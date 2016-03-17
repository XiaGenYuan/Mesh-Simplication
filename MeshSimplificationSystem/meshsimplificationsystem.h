#ifndef MESHSIMPLIFICATIONSYSTEM_H
#define MESHSIMPLIFICATIONSYSTEM_H

#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include <QtGui/QMainWindow>
#include <QVTKWidget.h>
#include <QFileDialog>
#include <vtkSmartPointer.h>
#include <vtkSTLReader.h>
#include <vtkSTLWriter.h> 
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindow.h>
#include <vtkAbstractArray.h>
#include <vtkCellArray.h>
#include <vector>
#include <queue>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <qtextcodec.h>
#include <qdialog.h>
#include <qmessagebox.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include "ui_meshsimplificationsystem.h"
#include "meshsimplifysetting.h"
#include "tools.h"

class MeshSimplificationSystem : public QMainWindow
{
	Q_OBJECT

public:
	MeshSimplificationSystem(QWidget *parent = 0,
		Qt::WFlags flags = 0);
	~MeshSimplificationSystem();
	void SetupMessageMap();                                  // 建立信号和槽
	void SetupComponent();                                   // 建立界面元素和类变量之间的对应关系                    
	void Init();                                             // 初始化函数
	void InitForSimplifying();                               // 网格简化前的一些初始化操作
	void EdgeContraction();                                  // 一次网格简化操作，即简化一个点
	void ComputeVertexMatrixQ( int id );                     // 计算某个定点的属性矩阵Q
	void ComputeEdgePair( int id_u, int id_v );              // 对一个点对计算新的位置
	void ClearVectors();                                     // 清理网格简化时用到的数组
	QString ShowContentFormat( int vertices, int faces );    // 格式化显示点和面的字符串
	void OpenFile( std::string filename );                   // 打开文件
	

public slots:
	void SlotOpenFiles();
	void SlotSaveas();
	void SlotClickSimplifying();
	void SlotSimplifying();          
	void SlotRecover();   

private:
	Ui::MeshSimplificationSystemClass ui;

private:
	QGroupBox *group_box_;                                    // 显示的主groupbox
	QVBoxLayout *main_layout_;                                // 主布局
	QVTKWidget *main_vtkwidget_;                              // 显示的主窗口
	QLabel *main_label_;                                      // 显示网格信息的label
	QAction *action_open_;                                    // 打开文件
	QAction *action_saveas_;                                  // 另存为
    QAction *action_mesh_simplification_;                     // 网格简化
	QAction *action_recover_;                                 // 恢复网格
	QStringList file_names_list_;                             // 打开文件的名字列表
	vtkSmartPointer< vtkPolyData > poly_data_;                // 三角网格数据
	vtkSmartPointer< vtkPolyData > pre_poly_data_;            // 三角网格数据
	vtkSmartPointer< vtkRenderer > renderer_;                 // 显示网格的renderer
	int number_of_points_;                                    // 网格中点的数量
	int number_of_existing_points_;                           // 网格中存在的点的个数
	int number_of_cells_;                                     // 网格中面片的数量
	int number_of_existing_cells_;                            // 网格中存在的点的个数
	std::vector< Point3D > points_;                           // 网格中点的集合
	std::vector< int > simplify_times_;                       // 记录每个点简化的次数
	std::vector< std::vector< int > > adjacency_edges_;       // 每个点的邻接边集合
	std::vector< std::vector< int > > planes_;                // 所有平面的集合
	std::vector< std::vector< int > > adjacency_planes_;      // 每个点的邻接平面集合
	std::vector< bool > still_existing_points_;               // 标记还存在的点
	std::vector< bool > still_existing_planes_;               // 标记还存在的平面
	std::vector< std::vector< double > > points_q_;           // 每个点的矩阵Q
	std::priority_queue< Edge > pri_cost_queue_;              // 每条边cost花费的优先队列
	std::priority_queue< Edge > pri_cost_queue_2_;            // 暂存优先队列
	int every_vertex_decrese_times_;                          // 每个点执行缩减的次数
	MeshSimplifySetting *mesh_simplify_setting_;              // 网格简化参数设置对话框
	bool is_success_simplified_;                              // 最近的一个是否成功地简化了
};

#endif // MESHSIMPLIFICATIONSYSTEM_H