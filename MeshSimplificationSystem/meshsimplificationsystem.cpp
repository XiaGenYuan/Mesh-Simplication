#include "meshsimplificationsystem.h"

MeshSimplificationSystem::MeshSimplificationSystem(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	this->SetupComponent();
	this->SetupMessageMap();
	this->Init();
}

MeshSimplificationSystem::~MeshSimplificationSystem()
{
}

void MeshSimplificationSystem::SetupComponent()
{
	this->group_box_ = new QGroupBox;
	this->main_layout_ = new QVBoxLayout;

	this->main_vtkwidget_ = new QVTKWidget;
	this->main_layout_->addWidget( this->main_vtkwidget_ );

	this->main_label_ = new QLabel;

	QString show_content( "vertices: 0 faces: 0" );

	this->main_label_->setText( show_content );
	this->main_label_->setAlignment( Qt::AlignCenter );
	this->main_layout_->addWidget( this->main_label_ );

	this->group_box_->setLayout( this->main_layout_ );

	this->mesh_simplify_setting_ = new MeshSimplifySetting( this );
	
	this->setCentralWidget( this->group_box_ );

	this->action_open_ = this->ui.action_open;
	this->action_open_->setShortcut( QKeySequence( Qt::CTRL + Qt::Key_O ) );

	this->action_saveas_ = this->ui.action_saveas;
	this->action_saveas_->setShortcut( QKeySequence( Qt::CTRL + Qt::Key_S ) );

	this->action_mesh_simplification_ = this->ui.action_mesh_simplification;
	this->action_mesh_simplification_->setShortcut( QKeySequence( Qt::CTRL + Qt::Key_M ) );

	this->action_recover_ = this->ui.action_recover;
	this->action_recover_->setShortcut( QKeySequence( Qt::CTRL + Qt::Key_R ) );
}

void MeshSimplificationSystem::SetupMessageMap()
{
	connect( this->action_open_, SIGNAL( triggered() ), this, SLOT( SlotOpenFiles() ) );
	connect( this->action_saveas_, SIGNAL( triggered() ), this, SLOT( SlotSaveas() ) );
	connect( this->action_mesh_simplification_, SIGNAL( triggered() ), this, SLOT( SlotClickSimplifying() ) );
	connect( this->mesh_simplify_setting_->confirm_button_, SIGNAL( clicked() ), this, SLOT( SlotSimplifying() ) );
	connect( this->action_recover_, SIGNAL( triggered() ), this, SLOT( SlotRecover() ) );
}

void MeshSimplificationSystem::Init()
{
	this->renderer_ = vtkSmartPointer< vtkRenderer > :: New();
	this->renderer_->SetBackground( 0.334, 0.510, 1 );
	this->main_vtkwidget_->GetRenderWindow()->AddRenderer( this->renderer_ );
	this->main_vtkwidget_->GetRenderWindow()->Render();
	this->every_vertex_decrese_times_ = 1;
}

void MeshSimplificationSystem::OpenFile( std::string filename )
{
	vtkSmartPointer< vtkSTLReader > reader =
		vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName( filename.c_str() );
	reader->Update();
	this->pre_poly_data_ = reader->GetOutput();
	this->poly_data_ = vtkSmartPointer< vtkPolyData >::New();
	this->poly_data_->DeepCopy( this->pre_poly_data_ );
	vtkSmartPointer< vtkPolyDataMapper > mapper =
		vtkSmartPointer< vtkPolyDataMapper >::New();
	mapper->SetInputConnection( reader->GetOutputPort() );
	
	vtkSmartPointer< vtkActor > actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper( mapper );
	
	//vtkSmartPointer< vtkRenderer > renderer = 
	//	vtkSmartPointer< vtkRenderer >::New();
	//this->renderer_->SetBackground( 0.334, 0.510, 1 );
	
	//vtkSmartPointer< vtkPropCollection > props = this->renderer_->GetViewProps(); //iterate through and set each visibility to 0
	//props->InitTraversal();
	//for( int i = 0; i < props->GetNumberOfItems(); i ++ )
	//{
	//	props->GetNextProp()->VisibilityOff();
	//	this->renderer_->ResetCamera();
	//	renderWindow->Render();
	//			
	//	renderWindowInteractor->Start();
	//}
			
	this->renderer_->RemoveAllViewProps();
	
	this->renderer_->AddActor( actor );
	this->renderer_->ResetCamera();
	//this->main_vtkwidget_->GetRenderWindow()->AddRenderer( renderer );
	this->main_vtkwidget_->GetRenderWindow()->Render();
}

void MeshSimplificationSystem::SlotOpenFiles()
{
	this->file_names_list_ = QFileDialog::getOpenFileNames( this, tr( "Open File" ), ".", 
		tr( "stl files(*.stl)" ) );
	if( !this->file_names_list_.isEmpty() )
	{
		int file_count = this->file_names_list_.size();
		for( int i = 0; i < file_count; ++ i )
		{
			OpenFile( this->file_names_list_.at( i ).toStdString() );
		}
		InitForSimplifying();
	}
}

void MeshSimplificationSystem::SlotSaveas()
{
	QString saveas_file_name = QFileDialog::getSaveFileName( this, tr( "Save File" ), 
		".", tr( "csv files(*.stl)" ) );
	if( saveas_file_name == "" || saveas_file_name.isEmpty() ||
		saveas_file_name.isNull() )
	{
		return;
	}
	if( this->poly_data_ == NULL )
	{
		return;
	}
	vtkSmartPointer< vtkSTLWriter > writer = vtkSmartPointer< vtkSTLWriter >::New();

	writer->SetInputData( this->poly_data_ );
	writer->SetFileName( saveas_file_name.toUtf8() );
	writer->Update();
	writer->SetFileTypeToBinary();
	writer->Write();
}

QString MeshSimplificationSystem::ShowContentFormat( int vertices, int faces )
{
	QString s_number_of_points = QString::number( vertices, 10 );
	QString s_number_of_cells = QString::number( faces, 10 );
	QString show_content( "vertices: " );
	show_content.append( s_number_of_points );
	show_content.append( " " );
	show_content.append( "faces: " );
	show_content.append( s_number_of_cells );
	return show_content;
}

void MeshSimplificationSystem::InitForSimplifying()
{
	ClearVectors();
	this->number_of_points_ = this->poly_data_->GetNumberOfPoints();
	this->number_of_existing_points_ = this->number_of_points_;
	this->number_of_cells_ = this->poly_data_->GetNumberOfCells();
	this->number_of_existing_cells_ = this->number_of_cells_;

	this->main_label_->setText( ShowContentFormat( this->number_of_points_, this->number_of_cells_ ) );

	this->points_.resize( this->number_of_points_ );
	this->simplify_times_.assign( this->number_of_points_, 0 );
	this->adjacency_edges_.resize( this->number_of_points_ );
	this->planes_.resize( this->number_of_cells_ );
	this->adjacency_planes_.resize( this->number_of_points_ );
	this->still_existing_points_.assign( this->number_of_points_, true );
	this->still_existing_planes_.assign( this->number_of_cells_, true );
	this->points_q_.resize( this->number_of_points_ );

	double p[ 3 ];
	for( int i = 0; i < this->number_of_points_; ++ i )
	{
		this->poly_data_->GetPoint( i, p );
		this->points_[ i ] = Point3D( p );
	}

	vtkSmartPointer< vtkIdList > id_list = vtkSmartPointer< vtkIdList >::New();
	for( int i = 0; i < this->number_of_cells_; ++ i )
	{
		this->poly_data_->GetCellPoints( i, id_list );
		for( int j = 0; j < 3; ++ j )
		{
			this->planes_[ i ].push_back( id_list->GetId( j ) );
			this->adjacency_planes_[ id_list->GetId( j ) ].push_back( i );
		}
		
		for( int j = 0; j < 3; ++ j )
		{
			int id_u = id_list->GetId( j );
			int id_v = id_list->GetId( ( j + 1 ) % 3 );

			bool flag = false;
			int len_u = this->adjacency_edges_[ id_u ].size();
			int len_v = this->adjacency_edges_[ id_v ].size();
			for( int k = 0; k < len_u; ++ k )
			{
				if( this->adjacency_edges_[ id_u ][ k ] == id_v )
				{
					flag = true;
					break;
				}
			}
			if( !flag )
			{
				this->adjacency_edges_[ id_u ].push_back( id_v );
			}

			flag = false;
			for( int k = 0; k < len_v; ++ k )
			{
				if( this->adjacency_edges_[ id_v ][ k ] == id_u )
				{
					flag = true;
					break;
				}
			}
			if( !flag )
			{
				this->adjacency_edges_[ id_v ].push_back( id_u );
			}
		}
	}
	//double paras[ 4 ];
	for( int i = 0; i < this->number_of_points_; ++ i )
	{
		ComputeVertexMatrixQ( i );
	}

	for( int i = 0; i < this->number_of_points_; ++ i )
	{
		std::vector< int > &id_list = this->adjacency_edges_[ i ];
		int id_size = id_list.size();
		for( int j = 0; j < id_size; ++ j )
		{
			if( i > id_list[ j ] )
			{
				continue;
			}

			int id_u = i;
			int id_v = id_list[ j ];
			ComputeEdgePair( id_u, id_v );
		}
	}
}

void MeshSimplificationSystem::ComputeEdgePair( int id_u, int id_v )
{
	double distance_uv = this->points_[ id_u ].GetDistance( this->points_[ id_v ] );
	std::vector< double > matrix_q( 16, 0 );
	for( int k = 0; k < 16; ++ k )
	{
		matrix_q[ k ] = this->points_q_[ id_u ][ k ] + this->points_q_[ id_v ][ k ];
	}

	//Eigen::Matrix4d Q;
	//for( int i = 0; i < 12; ++ i )
	//{
	//	 Q( i / 4, i % 4 ) = matrix_q[ i ];
	//}
	//Q( 3, 0 ) = Q( 3, 1 ) = Q( 3, 2 ) = 0;
	//Q( 3, 3 ) = 1;
	//Eigen::Vector4d b;
	//b( 0 ) = b( 1 ) = b( 2 ) = 0;
	//b( 3 ) = 1;
	//if( Q.determinant() != 0 )
	//{
	//	Eigen::Vector4d x = Q.colPivHouseholderQr().solve( b );
	//	Point3D middle_x( x( 0 ), x( 1 ), x( 2 ) );
	//	double cost_x = Plane::ComputeCost( middle_x, matrix_q );
	//	this->points_[ id_u ].ResetValue( middle_x );
	//	this->pri_cost_queue_.push( Edge( id_u, id_v, cost_x * distance_uv, 0 ) );
	//	return;
	//}


	Point3D middle_p = this->points_[ id_u ].GetMiddlePoint3D( this->points_[ id_u ], 
		                                                       this->points_[ id_v ] );
	double cost_u = Plane::ComputeCost( this->points_[ id_u ], matrix_q );
	double cost_v = Plane::ComputeCost( this->points_[ id_v ], matrix_q );
	double cost_uv2 = Plane::ComputeCost( middle_p, matrix_q );

	if( cost_u <= cost_v && cost_u <= cost_uv2 )
	{
		this->pri_cost_queue_.push( Edge( id_u, id_v, cost_u * distance_uv, 0 ) );
	}
	else if( cost_v <= cost_u && cost_v <= cost_uv2 )
	{
		this->pri_cost_queue_.push( Edge( id_u, id_v, cost_v * distance_uv, 1 ) );
	}
	else
	{
		this->pri_cost_queue_.push( Edge( id_u, id_v, cost_uv2 * distance_uv, 2 ) );
	}

}

void MeshSimplificationSystem::EdgeContraction()
{
	this->is_success_simplified_ = false;
	// 改变v1的坐标值
	if( this->pri_cost_queue_.empty() )
	{
		vtkSmartPointer< vtkSTLWriter > writer = vtkSmartPointer< vtkSTLWriter >::New();

		writer->SetInputData( this->poly_data_ );
		writer->SetFileName( "temp.stl" );
		writer->Update();
		writer->SetFileTypeToBinary();
		writer->Write();
		OpenFile( "temp.stl" );
		remove("temp.stl");
		InitForSimplifying();
		//return;
	}
	Edge top_edge = this->pri_cost_queue_.top();
	this->pri_cost_queue_.pop();

	this->number_of_existing_points_ --;
	this->number_of_existing_cells_ -= 2;

	this->simplify_times_[ top_edge.u_ ] ++;
	this->simplify_times_[ top_edge.v_ ] ++;
	if( top_edge.type_ == 1 )
	{
		this->points_[ top_edge.u_ ].ResetValue( this->points_[ top_edge.v_ ] );
	}
	else if( top_edge.type_ == 2 )
	{
		this->points_[ top_edge.u_ ].x_ = ( this->points_[ top_edge.u_ ].x_ +
			                                this->points_[ top_edge.v_ ].x_ ) / 2;
		this->points_[ top_edge.u_ ].y_ = ( this->points_[ top_edge.u_ ].y_ +
											this->points_[ top_edge.v_ ].y_ ) / 2;
		this->points_[ top_edge.u_ ].z_ = ( this->points_[ top_edge.u_ ].z_ +
											this->points_[ top_edge.v_ ].z_ ) / 2;
	}
	// 将节点v标记为删除状态
	this->still_existing_points_[ top_edge.v_ ] = false;

	// 将v的邻接顶点加入到u的邻接表里去，并更改与v邻接的那些点的邻接表
	std::vector< int > &ids_u = this->adjacency_edges_[ top_edge.u_ ];
	std::vector< int > &ids_v = this->adjacency_edges_[ top_edge.v_ ];
	int ids_u_size = ids_u.size();
	int ids_v_size = ids_v.size();
	std::vector< int > common_ids;
	std::vector< int > v_unique_ids;
	std::vector< int > u_unique_ids;
	for( int i = 0; i < ids_v_size; ++ i )
	{
		if( ids_v[ i ] == top_edge.u_ )
		{
			continue;
		}
		bool flag = false;
		for( int j = 0; j < ids_u_size; ++ j )
		{
			if( ids_v[ i ] == ids_u[ j ] )
			{
				common_ids.push_back( ids_v[ i ] );
				flag = true;
				break;
			}
		}

		if( !flag )
		{
			v_unique_ids.push_back( ids_v[ i ] );
			ids_u.push_back( ids_v[ i ] );
		}
	}
	for( int i = 0; i < ids_u_size; ++ i )
	{
		if( ids_u[ i ] == top_edge.v_ )
		{
			continue;
		}
		bool flag = false;
		for( int j = 0; j < ids_v_size; ++ j )
		{
			if( ids_u[ i ] == ids_v[ j ] )
			{
				flag = true;
				break;
			}
		}
		if( !flag )
		{
			u_unique_ids.push_back( ids_u[ i ] );
		}
	}
	// 删除u邻接表中的v节点
	ids_u_size = ids_u.size();
	for( int i = 0; i < ids_u_size; ++ i )
	{
		if( ids_u[ i ] == top_edge.v_ )
		{
			ids_u.erase( ids_u.begin() + i );
			break;
		}
	}

	// 删除节点u和节点v公共邻接点的邻接表中的v值
	int common_ids_size = common_ids.size();
	for( int i = 0; i < common_ids_size; ++ i  )
	{
		std::vector< int > &ids_adj = this->adjacency_edges_[ common_ids[ i ] ];
		int ids_adj_size = ids_adj.size();
		for( int j = 0; j < ids_adj_size; ++ j )
		{
			if( ids_adj[ j ] == top_edge.v_ )
			{
				ids_adj.erase( ids_adj.begin() + j );
				break;
			}
		}
	}

	// 修改节点u和节点v非公共邻接点的邻接表中的v值
	int v_unique_ids_size = v_unique_ids.size();
	for( int i = 0; i < v_unique_ids_size; ++ i )
	{
		std::vector< int > &ids_adj = this->adjacency_edges_[ v_unique_ids[ i ] ];
		int ids_adj_size = ids_adj.size();
		for( int j = 0; j < ids_adj_size; ++ j )
		{
			if( ids_adj[ j ] == top_edge.v_ )
			{
				ids_adj[ j ] == top_edge.u_;
				break;
			}
		}
	}

	// 修改节点u的邻接平面
	std::vector< int > &v_planes = this->adjacency_planes_[ top_edge.v_ ];
	int v_planes_size = v_planes.size();
	for( int i = 0; i < v_planes_size; ++ i )
	{
		int plane_id = v_planes[ i ];
		std::vector< int > &plane = this->planes_[ plane_id ];
		int plane_size = plane.size();
		if( plane_size != 3 ) continue;
		if( plane[ 0 ] == top_edge.u_ || plane[ 1 ] == top_edge.u_ || plane[ 2 ] == top_edge.u_ )
		{
			continue;
		}
		for( int j = 0; j < plane_size; ++ j )
		{
			if( plane[ j ] == top_edge.v_ )
			{
				plane[ j ] = top_edge.u_;
				this->adjacency_planes_[ top_edge.u_ ].push_back( plane_id );
				break;
			}
		}
	}

	// 去除节点u和v的公共点的多余邻接平面
	for( int i = 0; i < common_ids_size; ++ i  )
	{
		int common_id = common_ids[ i ];
		std::vector< int > &planes_adj = this->adjacency_planes_[ common_id ];
		int planes_adj_size = planes_adj.size();
		for( int j = 0; j < planes_adj_size; ++ j )
		{
			int plane_id = planes_adj[ j ];
			std::vector< int > &plane = this->planes_[ plane_id ];
			if( plane.size() != 3 )
			{
					continue;
			}
			if( ( plane[ 0 ] == top_edge.u_ || plane[ 1 ] == top_edge.u_ || plane[ 2 ] == top_edge.u_ ) && 
				( plane[ 0 ] == top_edge.v_ || plane[ 1 ] == top_edge.v_ || plane[ 2 ] == top_edge.v_ ) )
			{
				planes_adj.erase( planes_adj.begin() + j );
				break;
			}
		}
	}

	// 去除节点u邻接平面中的多余平面
	std::vector< int > &planes_adj = this->adjacency_planes_[ top_edge.u_ ];
	for( int j = 0; j < planes_adj.size(); ++ j )
	{
		int plane_id = planes_adj[ j ];
		std::vector< int > &plane = this->planes_[ plane_id ];
		if( plane.size() != 3 )
		{
			continue;
		}
		if(	plane[ 0 ] == top_edge.v_ || plane[ 1 ] == top_edge.v_ || plane[ 2 ] == top_edge.v_  )
		{
			this->still_existing_planes_[ plane_id ] = false;
			planes_adj.erase( planes_adj.begin() + j );
			j = -1;
		}
	}

	// 计算节点u的矩阵Q
	ComputeVertexMatrixQ( top_edge.u_ );

	// 计算节点u的所有邻接顶点的矩阵Q
	ids_u_size = ids_u.size();
	for( int i = 0; i < ids_u_size; ++ i )
	{
		ComputeVertexMatrixQ( ids_u[ i ] );
	}

	// 将新的边加入到优先队列中去
	for( int i = 0; i < common_ids_size; ++ i )
	{
		ComputeEdgePair( top_edge.u_, common_ids[ i ] );
	}
	for( int i = 0; i < v_unique_ids_size; ++ i )
	{
		ComputeEdgePair( top_edge.u_, v_unique_ids[ i ] );
	}
	int u_unique_ids_size = u_unique_ids.size();
	for( int i = 0; i < u_unique_ids_size; ++ i )
	{
		ComputeEdgePair( top_edge.u_, u_unique_ids[ i ] );
	}
	//for( int i = 0; i < ids_v_size; ++ i )
	//{
	//	for( int j = i + 1; j < ids_v_size; ++ j )
	//	{
	//		std::vector< int > &j_adj = this->adjacency_edges_[ ids_v [ j ] ];
	//		int j_adj_size = j_adj.size();
	//		for( int k = 0; k < j_adj_size; ++ k )
	//		{
	//			if( ids_v[ i ] == j_adj[ k ] )
	//			{
	//				ComputeEdgePair( ids_v[ i ], ids_v[ j ] );
	//				break;
	//			}
	//		}
	//	}
	//}

	ids_u_size = ids_u.size();
	for( int i = 0; i < ids_u_size; ++ i )
	{
		for( int j = i + 1; j < ids_u_size; ++ j )
		{
			std::vector< int > &j_adj = this->adjacency_edges_[ ids_u [ j ] ];
			int j_adj_size = j_adj.size();
			for( int k = 0; k < j_adj_size; ++ k )
			{
				if( ids_u[ i ] == j_adj[ k ] )
				{
					ComputeEdgePair( ids_u[ i ], ids_u[ j ] );
					break;
				}
			}
		}
	}

	while( true )
	{
		//if( this->still_existing_points_[ this->pri_cost_queue_.top().u_ ] && 
		//	this->still_existing_points_[ this->pri_cost_queue_.top().v_ ] )
		//{
		//	break;
		//}
		//else
		//{
		//	this->pri_cost_queue_.pop();
		//}
		//if( this->pri_cost_queue_.empty() )
		//{
		//	break;
		//}
		if( this->still_existing_points_[ this->pri_cost_queue_.top().u_ ] && 
			this->still_existing_points_[ this->pri_cost_queue_.top().v_ ] )
		{
			if( this->simplify_times_[ this->pri_cost_queue_.top().u_ ] < this->every_vertex_decrese_times_  && 
				this->simplify_times_[ this->pri_cost_queue_.top().v_ ] < this->every_vertex_decrese_times_  )
			{
				break;
			}
			else
			{
				this->pri_cost_queue_2_.push( this->pri_cost_queue_.top() );
				this->pri_cost_queue_.pop();
				if( this->pri_cost_queue_.empty() )
				{
					if( this->pri_cost_queue_2_.empty() )
					{
						break;
					}
					this->every_vertex_decrese_times_ += 1;
					while( !this->pri_cost_queue_2_.empty() )
					{
						this->pri_cost_queue_.push( this->pri_cost_queue_2_.top() );
						this->pri_cost_queue_2_.pop();
					}
				}				
			}			
		}
		else
		{
			this->pri_cost_queue_.pop();
			if( this->pri_cost_queue_.empty() )
			{
				if( !this->pri_cost_queue_2_.empty() )
				{
					this->every_vertex_decrese_times_ += 1;
					while( !this->pri_cost_queue_2_.empty() )
					{
						this->pri_cost_queue_.push( this->pri_cost_queue_2_.top() );
						this->pri_cost_queue_2_.pop();
					}
				}
				else
				{
					break;
				}				
			}
		}
	}
	this->is_success_simplified_ = true;
}

void MeshSimplificationSystem::ComputeVertexMatrixQ( int id )
{
	double paras[ 4 ];
	this->points_q_[ id ].clear();
	this->points_q_[ id ].assign( 16, 0.0 );
	std::vector< int > &all_planes = this->adjacency_planes_[ id ];
	int plane_size = all_planes.size();
	if( 0 == plane_size ) return;
	for( int j = 0; j < plane_size; ++ j )
	{
		int plane_id = all_planes[ j ];
		std::vector< int > &three_ids = this->planes_[ plane_id ];
		Plane::GetFourParametersFromThreePoints( this->points_[ three_ids[ 0 ] ], 
			this->points_[ three_ids[ 1 ] ], 
			this->points_[ three_ids[ 2 ] ], paras );
	}
	for( int j = 0; j < 4; ++ j )
	{
		for( int k = 0; k < 4; ++ k )
		{
			this->points_q_[ id ][ j * 4 + k ] = paras[ j ] * paras[ k ];
		}
	}
}

void MeshSimplificationSystem::SlotClickSimplifying( )
{
	this->mesh_simplify_setting_->show();
}


void MeshSimplificationSystem::SlotSimplifying( )
{
	if( this->poly_data_ == NULL )
	{
		return;
	}	
	if( this->mesh_simplify_setting_->radio_button_rate_->isChecked() )
	{
		if( this->mesh_simplify_setting_->radio_button_rate_vertex_->isChecked() )
		{
			double rate = this->mesh_simplify_setting_->lineedit_rate_vertex_->text().toDouble();
			if( rate < 0 || rate > 1 )
			{
				return;
			}
			int left  = ( int ) ( this->number_of_existing_points_ * rate );
			while( this->number_of_existing_points_ > left )
			{
				EdgeContraction();
				if( !this->is_success_simplified_ )
				{
					break;
				}
			}
		}
		else if( this->mesh_simplify_setting_->radio_button_rate_face_->isChecked() )
		{
			double rate = this->mesh_simplify_setting_->lineedit_rate_face_->text().toDouble();
			if( rate < 0 || rate > 1 )
			{
				return;
			}
			int left  = ( int ) ( this->number_of_existing_cells_ * rate );
			while( this->number_of_existing_cells_ > left )
			{
				EdgeContraction();
				if( !this->is_success_simplified_ )
				{
					break;
				}
			}
		}
	}
	else if( this->mesh_simplify_setting_->radio_button_number_->isChecked() )
	{
		if( this->mesh_simplify_setting_->radio_button_number_vertex_->isChecked() )
		{
			int left  = this->mesh_simplify_setting_->lineedit_number_vertex_->text().toInt();
			while( this->number_of_existing_points_ > left )
			{
				EdgeContraction();
				if( !this->is_success_simplified_ )
				{
					break;
				}
			}
		}
		else if( this->mesh_simplify_setting_->radio_button_number_face_->isChecked() )
		{
			int left  = this->mesh_simplify_setting_->lineedit_number_face_->text().toInt();
			while( this->number_of_existing_cells_ > left )
			{
				EdgeContraction();
				if( !this->is_success_simplified_ )
				{
					break;
				}
			}
		}
	}
		

	for( int i = 0; i < this->number_of_points_; ++ i )
	{
		if( this->still_existing_points_[ i ] )
		{
			double newp[ 3 ];
			newp[ 0 ] = this->points_[ i ].x_;
			newp[ 1 ] = this->points_[ i ].y_;
			newp[ 2 ] = this->points_[ i ].z_;
			this->poly_data_->GetPoints()->SetPoint( i, newp );
		}
	}

	this->poly_data_->DeepCopy( this->pre_poly_data_ );
	this->number_of_cells_ = this->poly_data_->GetNumberOfCells();
	vtkSmartPointer< vtkCellArray > cells = vtkSmartPointer< vtkCellArray >::New();
	for( int i = 0; i < this->number_of_cells_; ++ i )
	{
		vtkSmartPointer< vtkIdList > id_list = vtkSmartPointer< vtkIdList >::New();
		this->poly_data_->GetCellPoints( i, id_list );
		for( int j = 0; j < 3; ++ j )
		{
			id_list->SetId( j, this->planes_[ i ][ j ] );
		}
		cells->InsertNextCell( id_list );
	}
	this->poly_data_->SetPolys( cells );
	for( int i = 0; i < this->number_of_cells_; ++ i )
	{
		if( this->still_existing_planes_[ i ] == false )
		{
			this->poly_data_->DeleteCell( i );
		}
	}
	this->poly_data_->RemoveDeletedCells();
	vtkSmartPointer< vtkPolyDataMapper > mapper =
		vtkSmartPointer< vtkPolyDataMapper >::New();
	mapper->SetInputData( this->poly_data_ );

	vtkSmartPointer< vtkActor > actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper( mapper );

	//vtkSmartPointer< vtkRenderer > renderer = 
	//	vtkSmartPointer< vtkRenderer >::New();
	//renderer->SetBackground( 0.334, 0.510, 1 );

	this->renderer_->RemoveAllViewProps();
	this->renderer_->AddActor( actor );
	this->renderer_->ResetCamera();
	//this->main_vtkwidget_->GetRenderWindow()->AddRenderer( this->renderer_ );
	this->main_vtkwidget_->GetRenderWindow()->Render();

	this->main_label_->setText( ShowContentFormat( this->number_of_existing_points_, this->number_of_existing_cells_ ) );
}

void MeshSimplificationSystem::ClearVectors()
{
	if( this->points_.size() > 0 )
	{
		this->points_.clear();
	}
	if( this->simplify_times_.size() > 0 )
	{
		this->simplify_times_.clear();
	}
	if( this->adjacency_edges_.size() > 0 )
	{
		this->adjacency_edges_.clear();
	}
	if( this->planes_.size() > 0 )
	{
		this->planes_.clear();
	}
	if( this->adjacency_planes_.size() > 0 )
	{
		this->adjacency_planes_.clear();
	}
	if( this->still_existing_points_.size() > 0 )
	{
		this->still_existing_points_.clear();
	}
	if( this->still_existing_planes_.size() > 0 )
	{
		this->still_existing_planes_.clear();
	}
	if( this->points_q_.size() > 0 )
	{
		this->points_q_.clear();
	}
	while( this->pri_cost_queue_.size() > 0 )
	{
		this->pri_cost_queue_.pop();
	}
}

void MeshSimplificationSystem::SlotRecover()
{
	int file_count =  this->file_names_list_.size();
	for( int i = 0; i < file_count; ++ i )
	{
		OpenFile( this->file_names_list_.at( i ).toStdString() );
	}
	InitForSimplifying();
}