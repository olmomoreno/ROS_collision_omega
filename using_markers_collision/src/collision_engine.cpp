#include "/home/olmo/jade_workspace/src/using_markers_collision/include/collision_engine_oo.h"


CE_OO::CE_OO(ros::NodeHandle *nh){
    n=nh;
    c_r_c_pub = n->advertise<geometry_msgs::PoseStamped>("set_pos_c_r_c", 1000);
    c_g_c_pub = n->advertise<geometry_msgs::PoseStamped>("set_pos_c_g_c", 1000);
    sub_c_r_c = n->subscribe("feed_pos_c_r_c", 1000, &CE_OO::positionCallbackR, this);
    sub_c_g_c = n->subscribe("feed_pos_c_g_c", 1000, &CE_OO::positionCallbackG, this);
    initialize_stuff();
}

void CE_OO::initialize_stuff(){

}

bool CE_OO::run(){
    ros::Rate r(100);
    while (ros::ok())
    {
        ros::spinOnce();

	if((c_g_c_msg.pose.position.x+1)>=c_r_c_msg.pose.position.x){
		c_r_c_msg.pose.position.x = c_r_c_msg.pose.position.x + 0.01;
        }
	else{
		if(c_g_c_msg.pose.position.x>=1){
			c_g_c_msg.pose.position.x = -5.0;
			c_r_c_msg.pose.position.x = 0.0;
		}
		else{
			c_g_c_msg.pose.position.x = c_g_c_msg.pose.position.x + 0.01;
		}
	}
    	c_r_c_pub.publish(c_r_c_msg);
        c_g_c_pub.publish(c_g_c_msg);
        r.sleep();
    }
}

void CE_OO::positionCallbackR(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    c_r_c_msg=*msg;
    
    //ROS_INFO("I heard [%f]:", pose.pose.position.y);
    //marker.pose=msg->pose;
}

void CE_OO::positionCallbackG(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    c_g_c_msg=*msg;
    
    //ROS_INFO("I heard [%f]:", pose.pose.position.y);
    //marker.pose=msg->pose;
}

int main( int argc, char** argv )
{
    ros::init(argc, argv, "collision_engine");
    ros::NodeHandle n;
    CE_OO instance(&n);
    instance.run();
}

