#include "ros/ros.h"
#include "epos2/Velocity.h"
#include "wrap.h"
#include "geometry_msgs/Twist.h"
#include "time.h"
#include "std_msgs/Duration.h"

// initialising ros stuffs

void callback ( const geometry_msgs::Twist &vel )
{
//     ros::NodeHandle nh;
//     ros::Publisher time_diff = nh.advertise<std_msgs::Duration> ( "/time_diff",10 );
//     std_msgs::Duration diff;
//     ros::Time start = ros::Time::now();
  
    uint ulErrorCode = 0;
    double Vx,Vy,w,v1,v2,v3;
    double z=0.20; // the distance between a wheel and the center of base (unit: meter)
    double r=0.075; // wheel radius (unit: meter)
    
    Vx=vel.linear.x;
    Vy=vel.linear.y;
    w=vel.angular.z;

    v1 = Vy + w*z;
    v2 = ( ( -sqrt ( 3 ) /2 ) *Vx ) + ( -0.5*Vy ) + w*z;
    v3 = ( sqrt ( 3 ) /2 ) *Vx + ( -0.5*Vy ) + w*z;

    double scaler = 573; // 0.1 degree per second
    // Moving with calculated velocities
//    MoveWithVelocity ( g_pKeyHandle, 1, ( long ) (v1/r*scaler), &ulErrorCode );
//    MoveWithVelocity ( g_pKeyHandle, 2, ( long ) (v2/r*scaler), &ulErrorCode );
//    MoveWithVelocity ( g_pKeyHandle, 3, ( long ) (v3/r*scaler), &ulErrorCode );

    MoveWithVelocity ( g_pKeyHandle, 2, ( long ) (v1/r*scaler), &ulErrorCode );
    MoveWithVelocity ( g_pKeyHandle, 3, ( long ) (v2/r*scaler), &ulErrorCode );
    MoveWithVelocity ( g_pKeyHandle, 1, ( long ) (v3/r*scaler), &ulErrorCode );
    
//     ros::Time end = ros::Time::now();
//     diff.data = end - start;
//     time_diff.publish ( diff );
//     cout<<"time taken:"<<diff<<endl;

}

int main ( int argc, char **argv )
{

    int lResult = MMC_FAILED;
    unsigned int ulErrorCode = 0;
    int node;
    // Set parameter for usb IO operation
    SetDefaultParameters();
    // open device
    if ( ( lResult = OpenDevice ( &ulErrorCode ) ) !=MMC_SUCCESS ) {
        LogError ( "OpenDevice", lResult, ulErrorCode );
        return lResult;
    }

    //Activate all drivers
    SetEnableState ( g_pKeyHandle, 1, &ulErrorCode );
    ActivateProfileVelocityMode ( g_pKeyHandle, 1, &ulErrorCode );
    SetEnableState ( g_pKeyHandle, 2, &ulErrorCode );
    ActivateProfileVelocityMode ( g_pKeyHandle, 2, &ulErrorCode );
    SetEnableState ( g_pKeyHandle, 3, &ulErrorCode );
    ActivateProfileVelocityMode ( g_pKeyHandle, 3, &ulErrorCode );

    ros::init ( argc, argv, "control" );
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe ( "epos2/cmd_vel" , 5 ,&callback );
    ros::spin();
}

