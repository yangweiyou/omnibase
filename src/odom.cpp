

# Movement based on wheel velocity
else {//input->generic.type == open_base::Movement::VELOCITY
            if (input->generic.frame == open_base::Movement::MOBILE) {

                // direct mobile
                kinematicsInverse.request.input.x     = input->generic.target.x;
                kinematicsInverse.request.input.y     = input->generic.target.y;
                kinematicsInverse.request.input.theta = input;

case MOVEMENT_DIRECT_M:
                kinematicsInverseMobileClient.call(kinematicsInverse);
                velocity.v_left  = kinematicsInverse.response.output.v_left ;
                velocity.v_back  = kinematicsInverse.response.output.v_back ;
                velocity.v_right = kinematicsInverse.response.output.v_right;
                break;
// pushing wheel velocities to Kinematics.cpp

bool inverseWorld(open_base::KinematicsInverse::Request &request, open_base::KinematicsInverse::Response &response) {
    worldToMobileCore(request.input.x, request.input.y, request.input.x, request.input.y);
    inverseMobile(request, response);
    return true;
}// open 2 service

long double theta = 0;
void worldToMobileCore(double Vxw, double Vyw, double& Vxm, double& Vym) {
    Vxm =   (std::cos(theta) * Vxw) + (std::sin(theta) * Vyw);
    Vym = - (std::sin(theta) * Vxw) + (std::cos(theta) * Vyw);
} // getting pose of robot?

bool inverseMobile(open_base::KinematicsInverse::Request &request, open_base::KinematicsInverse::Response &response) {
    long double V__m_x2 = - request.input.x / 2.0L;
    long double sqrt3V__m_y2 = (sqrt3 * request.input.y) / 2.0L;
    long double Lomega_p = L * request.input.theta;
    response.output.v_left  = V__m_x2 - sqrt3V__m_y2 + Lomega_p;
    response.output.v_back  = request.input.x        + Lomega_p;
    response.output.v_right = V__m_x2 + sqrt3V__m_y2 + Lomega_p;
    return true;
} //calculating velocity?

bool forwardMobile(open_base::KinematicsForward::Request &request, open_base::KinematicsForward::Response &response) {
    response.output.x     = ((2.0L * request.input.v_back) - request.input.v_left - request.input.v_right) / 3.0L;
    response.output.y     = ((sqrt3 * request.input.v_right) - (sqrt3 * request.input.v_left)) / 3.0L;
    response.output.theta = (request.input.v_left + request.input.v_back + request.input.v_right) / L3;
    return true;
}
// calculating cmd_vel

bool forwardWorld(open_base::KinematicsForward::Request &request, open_base::KinematicsForward::Response &response) {
    forwardMobile(request, response); // get cmd_vel
    mobileToWorldCore(response.output.x, response.output.y, response.output.x, response.output.y);
    // use cmd_vel to get pose of world
    return true;
}

void mobileToWorldCore(double Vxm, double Vym, double& Vxw, double& Vyw) {
    Vxw = (std::cos(theta) * Vxm) - (std::sin(theta) * Vym);
    Vyw = (std::sin(theta) * Vxm) + (std::cos(theta) * Vym);
} // get kinematics relative to world

// odom.cpp

void onEncoderMessage(const open_base::Velocity::ConstPtr& input){
    // get wheel velocity and multiply by wheel radius
    service.request.input.v_left  = input->v_left  * r;
    service.request.input.v_back  = input->v_back  * r;
    service.request.input.v_right = input->v_right * r;
    timeCurrent = ros::Time::now()forwardMobile
    // get delta time
    duration = (timeCurrent - timePrevious).toSec();
    timePrevious = timeCurrent; // set current as prev time
    kinematicsForwardWorld.call(service); // call forwardworld
    poseWorld.x     = (service.response.output.x     * duration) + poseWorld.x    ;
    poseWorld.y     = (service.response.output.y     * duration) + poseWorld.y    ;
    poseWorld.theta = (service.response.output.theta * duration) + poseWorld.theta;
    // pose = kinematics relative to world* time_diff + world pose
    if ((!std::isnan(poseWorld.x)) && (!std::isnan(poseWorld.y)) && (!std::isnan(poseWorld.theta))) {
        publisherWorld.publish(poseWorld);
        poseWorld.x     = poseWorld.x    ;
        poseWorld.y     = poseWorld.y    ;
        poseWorld.theta = poseWorld.theta;
    }
    kinematicsForwardMobile.call(service); // get cmd_vel
    poseWorld.x     = (service.response.output.x     * duration) + poseMobile.x    ;
    poseWorld.y     = (service.response.output.y     * duration) + poseMobile.y    ;
    poseWorld.theta = (service.response.output.theta * duration) + poseMobile.theta;
    // cmd_vel* time_diff + mobile pose = robot pose
    if ((!std::isnan(poseWorld.x)) && (!std::isnan(poseWorld.y)) && (!std::isnan(poseWorld.theta))) {
        publisherMobile.publish(poseWorld);
        poseMobile.x     = poseWorld.x    ;
        poseMobile.y     = poseWorld.y    ;
        poseMobile.theta = poseWorld.theta;
    }
}


