#include <AccelStepper.h>
#include <MultiStepper.h>
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

// Configuration des broches pour le moteur Y
#define Y_STEP_PIN 3  // Broche STEP du moteur Y
#define Y_DIR_PIN 6   // Broche DIR du moteur Y

// Configuration des paramètres des moteurs
#define MOTOR_STEPS 3200  // Nombre de pas par tour du moteur
#define RPM 500000           // Vitesse de rotation en tours par minute
#define MICROSTEPS 1    // Configuration du microstepping (1/16 de pas)

// Définition des objets AccelStepper pour chaque moteur
AccelStepper stepperX(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperY(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);

// Créer un objet MultiStepper pour synchroniser les moteurs
MultiStepper multiStepper;
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
  editSpeed(5);

  // Activation des sorties des drivers pour les moteurs X et Y
  digitalWrite(ENABLE_PIN, LOW);  // Activer le driver du moteur X (LOW = activé)
  digitalWrite(ENABLE_PIN, LOW);  // Activer le driver du moteur Y (LOW = activé)

  // Ajouter les moteurs à la MultiStepper (X et Y)
  multiStepper.addStepper(stepperX);
  multiStepper.addStepper(stepperY);
}

//LOOP==================================================================================================
void loop() {
  Serial.println("[loop] starting mooving");
  moveTo(100);
  stepperX.runSpeedToPosition();
}

//FONCTION================================================================================================
// Fonction pour faire avancer le robot sur une distance donnée en mm
void  moveTo(float distance) {
  float distanceSteps = distance * MOTOR_STEPS * MICROSTEPS;  // TODO : Calcul du nombre de pas nécessaires
  stepperX.setCurrentPosition(0);
  stepperY.setCurrentPosition(0);
  stepperX.moveTo(distanceSteps);  // Déplacer les moteurs vers les positions cibles
}
void editSpeed(unsigned int speed = 1){
  stepperX.setMaxSpeed((float(MOTOR_STEPS * MICROSTEPS) / 60) * RPM/speed);
  stepperX.setAcceleration((float(MOTOR_STEPS * MICROSTEPS) / 60) * RPM/(speed*4));
  stepperY.setMaxSpeed((float(MOTOR_STEPS * MICROSTEPS) / 60) * RPM/speed);
  stepperY.setAcceleration((float(MOTOR_STEPS * MICROSTEPS) / 60) * RPM/(speed*4));
}
