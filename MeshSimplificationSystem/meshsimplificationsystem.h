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
	void SetupMessageMap();                                  // �����źźͲ�
	void SetupComponent();                                   // ��������Ԫ�غ������֮��Ķ�Ӧ��ϵ                    
	void Init();                                             // ��ʼ������
	void InitForSimplifying();                               // �����ǰ��һЩ��ʼ������
	void EdgeContraction();                                  // һ������򻯲���������һ����
	void ComputeVertexMatrixQ( int id );                     // ����ĳ����������Ծ���Q
	void ComputeEdgePair( int id_u, int id_v );              // ��һ����Լ����µ�λ��
	void ClearVectors();                                     // ���������ʱ�õ�������
	QString ShowContentFormat( int vertices, int faces );    // ��ʽ����ʾ�������ַ���
	void OpenFile( std::string filename );                   // ���ļ�
	

public slots:
	void SlotOpenFiles();
	void SlotSaveas();
	void SlotClickSimplifying();
	void SlotSimplifying();          
	void SlotRecover();   

private:
	Ui::MeshSimplificationSystemClass ui;

private:
	QGroupBox *group_box_;                                    // ��ʾ����groupbox
	QVBoxLayout *main_layout_;                                // ������
	QVTKWidget *main_vtkwidget_;                              // ��ʾ��������
	QLabel *main_label_;                                      // ��ʾ������Ϣ��label
	QAction *action_open_;                                    // ���ļ�
	QAction *action_saveas_;                                  // ���Ϊ
    QAction *action_mesh_simplification_;                     // �����
	QAction *action_recover_;                                 // �ָ�����
	QStringList file_names_list_;                             // ���ļ��������б�
	vtkSmartPointer< vtkPolyData > poly_data_;                // ������������
	vtkSmartPointer< vtkPolyData > pre_poly_data_;            // ������������
	vtkSmartPointer< vtkRenderer > renderer_;                 // ��ʾ�����renderer
	int number_of_points_;                                    // �����е������
	int number_of_existing_points_;                           // �����д��ڵĵ�ĸ���
	int number_of_cells_;                                     // ��������Ƭ������
	int number_of_existing_cells_;                            // �����д��ڵĵ�ĸ���
	std::vector< Point3D > points_;                           // �����е�ļ���
	std::vector< int > simplify_times_;                       // ��¼ÿ����򻯵Ĵ���
	std::vector< std::vector< int > > adjacency_edges_;       // ÿ������ڽӱ߼���
	std::vector< std::vector< int > > planes_;                // ����ƽ��ļ���
	std::vector< std::vector< int > > adjacency_planes_;      // ÿ������ڽ�ƽ�漯��
	std::vector< bool > still_existing_points_;               // ��ǻ����ڵĵ�
	std::vector< bool > still_existing_planes_;               // ��ǻ����ڵ�ƽ��
	std::vector< std::vector< double > > points_q_;           // ÿ����ľ���Q
	std::priority_queue< Edge > pri_cost_queue_;              // ÿ����cost���ѵ����ȶ���
	std::priority_queue< Edge > pri_cost_queue_2_;            // �ݴ����ȶ���
	int every_vertex_decrese_times_;                          // ÿ����ִ�������Ĵ���
	MeshSimplifySetting *mesh_simplify_setting_;              // ����򻯲������öԻ���
	bool is_success_simplified_;                              // �����һ���Ƿ�ɹ��ؼ���
};

#endif // MESHSIMPLIFICATIONSYSTEM_H