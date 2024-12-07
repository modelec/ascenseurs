#include <AccelStepper.h>
//POSITION-------------------------------------------------------------------------------------------
void moveTo(float distance);
void end();
void editSpeed(unsigned int speed = 1);

//MOTEURS--------------------------------------------------------------------------------------------
// Configuration des broches pour le moteur X
#define X_STEP_PIN 2  // Broche STEP du moteur X
#define X_DIR_PIN 5   // Broche DIR du moteur X
#define ENABLE_PIN 8  // Broche ENABLE du moteur

#define M0_PIN 9   // Broche M0 du moteur X
#define M1_PIN 10  // Broche M1 du moteur X
#define M2_PIN 11  // Broche M2 du moteur X

// Configuration des paramètres des moteurs
#define MOTOR_STEPS 200  // Nombre de pas par tour du moteur
#define RPM 50             // Vitesse de rotation en tours par minute
#define MICROSTEPS 16    // Configuration du microstepping (1/16 de pas)

#define SPEED 5

// Définition des objets AccelStepper pour chaque moteur
AccelStepper stepperX(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);

// Garder en mémoire la position de l'ascenseur
long position;


//SETUP================================================================================================
void setup() {
  Serial.begin(9600);

  while (!Serial) {}
  Serial.println("[setup] Starting ascensor programm");

  //CONFIG MOTEURS--------------------------------------------------------------------------------------------

  // Configuration des broches pour le moteur X
  pinMode(ENABLE_PIN, OUTPUT);

  // Configuration des paramètres des moteurs X et Y
  //editSpeed(5);
  stepperX.setMaxSpeed((float(MOTOR_STEPS * MICROSTEPS) / 60) * RPM/SPEED);
  stepperX.setAcceleration((float(MOTOR_STEPS * MICROSTEPS) / 60) * RPM/(SPEED*4));

  // Activation des sorties des drivers pour les moteurs X et Y
  digitalWrite(ENABLE_PIN, LOW);  // Activer le driver du moteur X (LOW = activé)
  
  moveTo(1000);
}

//LOOP==================================================================================================
void loop() {
  Serial.println("[loop] starting mooving");
  stepperX.runSpeedToPosition();
}

//FONCTION================================================================================================
// Fonction pour faire avancer le robot sur une distance donnée en mm
void  moveTo(float distance) {
  float distanceSteps = distance * MOTOR_STEPS * MICROSTEPS;  // TODO : Calcul du nombre de pas nécessaires
  stepperX.setCurrentPosition(0);
  stepperX.moveTo(distanceSteps);  // Déplacer les moteurs vers les positions cibles
}
void editSpeed(unsigned int speed = 1){
  stepperX.setMaxSpeed((float(MOTOR_STEPS * MICROSTEPS) / 60) * RPM/speed);
  stepperX.setAcceleration((float(MOTOR_STEPS * MICROSTEPS) / 60) * RPM/(speed*4));
}
