#include "main.h"
#include "ports.hpp"
#include "Robot.hpp"
 #include "lemlib/api.hpp"  //IWYU pragma: keep

// pros::Motor left_front_motor(ports::LEFT_FRONT_TOP_DT, pros::MotorGearset::blue);
// pros::Motor left_middle_motor(ports::LEFT_FRONT_BOTTOM_DT, pros::MotorGearset::blue);
// pros::Motor left_back_motor(ports::LEFT_BACK_DT, pros::MotorGearset::blue);
// pros::Motor right_front_motor(ports::RIGHT_FRONT_TOP_DT, pros::MotorGearset::blue);
// pros::Motor right_middle_motor(ports::LEFT_FRONT_BOTTOM_DT, pros::MotorGearset::blue);
// pros::Motor right_back_motor(ports::LEFT_BACK_DT, pros::MotorGearset::blue);

// pros::MotorGroup left_side_motors({left_front_motor,left_middle_motor, left_back_motor});
// pros::MotorGroup right_side_motors({right_front_motor, right_middle_motor, right_back_motor});

pros::MotorGroup left_side_motors({ports::LEFT_FRONT_TOP_DT, ports::LEFT_FRONT_BOTTOM_DT, ports::LEFT_BACK_DT}, pros::MotorGearset::blue);
pros::MotorGroup right_side_motors({ports::RIGHT_FRONT_TOP_DT, ports::RIGHT_FRONT_BOTTOM_DT, ports::RIGHT_BACK_DT}, pros::MotorGearset::blue);

lemlib::Drivetrain drivetrain(
	&left_side_motors, //left motor group
	&right_side_motors, //right motor group
	14.9, //track width
	3.25, //wheel diameter
	450, //drivetrain rpm
	2 //horizontal drift
);

pros::Imu intertial_sensor(17); //add port

lemlib::OdomSensors sensors(
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	&intertial_sensor
);

// forward/backward PID
lemlib::ControllerSettings lateralController(
	60, // proportional gain (kP)
    0, // integral gain (kI)
    5, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    500, // large error range timeout, in milliseconds
    10 // maximum acceleration (slew)
);

// turning PID
lemlib::ControllerSettings angularController(
	2.75, // proportional gain (kP)
    0, // integral gain (kI)
    12, // derivative gain (kD)
    0, // anti windup
    0, // small error range, in inches
    0, // small error range timeout, in milliseconds
    0, // large error range, in inches
    0, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// pros::lcd::initialize();
	// pros::lcd::set_text(1, "Hello PROS User!");

	// pros::lcd::register_btn1_cb(on_center_button);
	// std::printf("hellox5544");


    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	Pneumatics pneu (ports::PNEUMATIC1);
	// Intake intake (ports::INTAKE_MOTOR_1, ports::INTAKE_MOTOR_2);

	chassis.setPose(0, 0, 0);

	// // chassis.turnToHeading(90, 1000);  // for angular PID tuning
	// // chassis.setPose(0, 0, 0);
	// // chassis.turnToHeading(-90, 100000);
	//chassis.moveToPoint(0, 24, 1000);   // for lateral PID tuning.

	//offensive
	// chassis.moveToPoint(0, -10, 100000); //change
	// pneu.set_mogo(true);
	// intake.move(600);
	// pros::delay(2); //change time
	// intake.stop();
	// chassis.moveToPose(10, 10, 45, 100000); //change
	// intake.move(600);
	// pros::delay(2); //change time
	// intake.move(-600);
	// pros::delay(2); //change time
	// intake.stop();


	//defensive
	chassis.moveToPoint(0, -48, 10000, {.forwards = false}); // moves forward
	chassis.moveToPose(-10, -10, 0, 10000, {.forwards = false}); //change. // positions bot between mogo and ring while facing mogo (idk if thats how method works)
	chassis.moveToPoint(0, -10, 1000, {.forwards = false}); //change. //moves forward
	pneu.set_mogo(true);  //grab mogo
	chassis.moveToPoint(0, 10, 1000); //change. //moves away from line


	// chassis.turnToHeading(0, 1000); //change. makes bot's mogo face mogo
	// chassis.turnToHeading(90, 1000); //change
	// chassis.moveToPoint(0, -24, 10000, {.forwards = false}); //change

	//chassis.moveToPose(-10, -10, 90, 10000, {.forwards = false}); //change
	//pneu.set_mogo(true);
	//chassis.moveToPose(10, 10, 45, 100000); //change
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


// void opcontrol() {
// 	pros::Controller master(pros::E_CONTROLLER_MASTER);
// 	pros::MotorGroup left_mg({ports::LEFT_BACK_DT, ports::LEFT_FRONT_BOTTOM_DT, ports::LEFT_FRONT_TOP_DT});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
// 	pros::MotorGroup right_mg({ports::RIGHT_BACK_DT, ports::RIGHT_FRONT_BOTTOM_DT, ports::RIGHT_FRONT_TOP_DT});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6


// 	while (true) {
// 		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
// 		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
// 		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

// 		// Arcade control scheme
// 		int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
// 		int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
// 		left_mg.move(dir - turn);                      // Sets left motor voltage
// 		right_mg.move(dir + turn);                     // Sets right motor voltage
// 		pros::delay(20);                               // Run for 20 ms then update
// 	}
// }

void opcontrol(){
	Robot robot (ports::LEFT_BACK_DT, ports::LEFT_FRONT_BOTTOM_DT, ports::LEFT_FRONT_TOP_DT, ports::RIGHT_BACK_DT, ports::RIGHT_FRONT_BOTTOM_DT, ports::RIGHT_FRONT_TOP_DT, ports::PNEUMATIC1, ports::INTAKE_MOTOR_1, ports::INTAKE_MOTOR_2);

	while(true) {
		robot.update("hi");
		std::printf("hellox2");
		pros::Task::delay(10);
	}
}