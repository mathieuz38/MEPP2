#ifndef TestPlugin_H
#define TestPlugin_H

#if(_MSC_VER >= 1400)
#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif
#endif

#include "Visualization/Plugins/PluginInterface.h"

#include <QStringList>
#include "Dialogs/DialogTest1.h"

#ifndef Q_MOC_RUN // MT : very important to avoid the error : ' Parse error at
                  // "BOOST_JOIN" ' -> (qt4 pb with boost)
#include "Visualization/PluginFilters/BasePlugin.h"
#include "Visualization/SimpleViewer.h"

#include "Visualization/SimpleWindow.h"

#include "FEVV/Filters/Generic/Manifold/test_filter.hpp" // A) include the header of the filter corresponding to your operation

#include "FEVV/Wrappings/properties.h"

#ifdef FEVV_USE_CGAL
#include "FEVV/Wrappings/properties_polyhedron_3.h"
#include "FEVV/Wrappings/properties_surface_mesh.h"
#include "FEVV/Wrappings/properties_linear_cell_complex.h"
#endif // FEVV_USE_CGAL
#ifdef FEVV_USE_OPENMESH
#include "FEVV/Wrappings/properties_openmesh.h"
#endif // FEVV_USE_OPENMESH
#ifdef FEVV_USE_AIF
#include "FEVV/Wrappings/properties_aif.h"
#endif // FEVV_USE_AIF
#endif

namespace FEVV {

class TestPlugin : public QObject,
                         public Generic_PluginInterface,
                         public BasePlugin
{
  Q_OBJECT
  Q_INTERFACES(FEVV::Generic_PluginInterface)
#if(FEVV_USE_QT5) // see at the end of .cpp for QT4
  Q_PLUGIN_METADATA(IID "TestPlugin")
#endif

  /*public:
      using BasePlugin::apply;*/
public:
  TestPlugin() = default;
  ~TestPlugin() = default;

public:
  void init() override { init(true, 1.0, 1.0, 1.0); }

  void init(bool _forceCompute, double _x, double _y, double _z)
  {
    *value_forceCompute = _forceCompute;

    *value_x = _x;
    *value_y = _y;
    *value_z = _z;
  }

  void reset() override
  {
    init();

    emit resetSignal();
  }

  void addParameters(BaseWindow *_window) override
  {
    window = _window;
    if(window == nullptr || !window->isInit())
    {
      std::cerr << "BaseWindow is null or not initialized." << std::endl;
      return;
    }

    // window->setParam( "(Qt) Test: X", value_x, "test_qt_p", this );
    // window->setParam( "(Qt) Test: Y", value_y, "test_qt_p", this );
    // window->setParam( "(Qt) Test: Z", value_z, "test_qt_p", this );
  }

  template< typename HalfedgeGraph >
  void process(HalfedgeGraph *_mesh)
  {
    std::cout << "Asking to Test mesh ! " << std::endl;

    auto pm = get(boost::vertex_point, *_mesh);

    test_filter( // B) call the filter corresponding to your
                                // operation
        *_mesh,
        pm);

    std::cout << "Test mesh of " << *value_x << ";" << *value_y << ";"
              << *value_z << "." << std::endl;
  }

  template< typename HalfedgeGraph >
  void applyHG(BaseAdapterVisu *_adapter,
               HalfedgeGraph *_mesh,
               FEVV::PMapsContainer *pmaps_bag)
  {
    if(*value_forceCompute)
      process(_mesh);

    SimpleViewer< HalfedgeGraph > *viewer =
        dynamic_cast< SimpleViewer< HalfedgeGraph > * >(_adapter->getViewer());
    if(viewer)
      viewer->draw_or_redraw_mesh(_mesh, pmaps_bag, true, false);

    reset();

    viewer->frame();
  }

#ifdef FEVV_USE_OPENMESH
  void apply(BaseAdapterVisu *_adapter,
             MeshOpenMesh *_mesh,
             FEVV::PMapsContainer *pmaps_bag) override
  {
    applyHG< MeshOpenMesh >(_adapter, _mesh, pmaps_bag);
  }
#endif

#ifdef FEVV_USE_CGAL
  void apply(BaseAdapterVisu *_adapter,
             MeshLCC *_mesh,
             FEVV::PMapsContainer *pmaps_bag) override
  {
    applyHG< MeshLCC >(_adapter, _mesh, pmaps_bag);
  }

  void apply(BaseAdapterVisu *_adapter,
             MeshSurface *_mesh,
             FEVV::PMapsContainer *pmaps_bag) override
  {
    applyHG< MeshSurface >(_adapter, _mesh, pmaps_bag);
  }

  void apply(BaseAdapterVisu *_adapter,
             MeshPolyhedron *_mesh,
             FEVV::PMapsContainer *pmaps_bag) override
  {
    applyHG< MeshPolyhedron >(_adapter, _mesh, pmaps_bag);
  }
#endif

#ifdef FEVV_USE_AIF
  void apply(BaseAdapterVisu *_adapter,
             MeshAIF *_mesh,
             FEVV::PMapsContainer *pmaps_bag) override
  {
    applyHG< MeshAIF >(_adapter, _mesh, pmaps_bag);
  }
#endif

  QStringList Generic_plugins() const override
  {
    return QStringList() << "TestPlugin";
  }

  bool Generic_plugin(const QString &plugin) override
  {
    DialogTest1 dial1;
    dial1.setProcess(*value_x, *value_y, *value_z);
    if(dial1.exec() == QDialog::Accepted)
    {
      dial1.getProcess(*value_x, *value_y, *value_z);

      SimpleWindow *sw = static_cast< SimpleWindow * >(
          window); // dynamic_cast fails under OS X

      sw->onModificationParam("test_qt_p", this);
      sw->onApplyButton();

      return true;
    }

    return false;
  }


signals:
  void resetSignal();

protected:
  bool *value_forceCompute = new bool(false);

  double *value_x = new double(0.0);
  double *value_y = new double(0.0);
  double *value_z = new double(0.0);
};

} // namespace FEVV

#endif // TestPlugin_H
