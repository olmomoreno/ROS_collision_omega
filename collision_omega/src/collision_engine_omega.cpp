#include "/home/olmo/jade_workspace/src/collision_omega/include/collision_engine_omega_oo.h"

CE_OO::CE_OO(ros::NodeHandle *nh){
    n=nh;
    c_r_c_pub = n->advertise<geometry_msgs::PoseStamped>("set_pos_c_r_c", 1000);
    c_g_c_pub = n->advertise<geometry_msgs::PoseStamped>("set_pos_c_g_c", 1000);
    chatter_pub = n->advertise<std_msgs::Int64>("chatter", 1000);
    sub_c_r_c = n->subscribe("feed_pos_c_r_c", 1000, &CE_OO::positionCallbackR, this);
    sub_c_g_c = n->subscribe("feed_pos_c_g_c", 1000, &CE_OO::positionCallbackG, this);
    sub_omega = n->subscribe("feed_pos_omega", 1000, &CE_OO::positionCallbackOmega, this);
}

bool CE_OO::run(){
    ros::Rate r(100);
    while (ros::ok())
    {
    ros::spinOnce();
	if((c_g_c_msg.pose.position.x+1)>=c_r_c_msg.pose.position.x){
        c_r_c_msg.pose.position.x = c_g_c_msg.pose.position.x + 1;
        flag_collision.data=1;
        }
    else{
        flag_collision.data = 0;
    }
    if((c_g_c_msg.pose.position.x) <= -3){
        c_r_c_msg.pose.position.x = 0.0;
        }
    	c_r_c_pub.publish(c_r_c_msg);
        chatter_pub.publish(flag_collision);
        r.sleep();
    }
}

void CE_OO::positionCallbackR(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    c_r_c_msg=*msg;
}

void CE_OO::positionCallbackG(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    c_g_c_msg=*msg;
}

void CE_OO::positionCallbackOmega(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    omega_msg=*msg;
    c_g_c_pub.publish(omega_msg);
}

int main( int argc, char** argv )
{
    ros::init(argc, argv, "collision_engine_omega");
    ros::NodeHandle n;
    CE_OO instance(&n);
    instance.run();
}
