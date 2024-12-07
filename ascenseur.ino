#include <AccelStepper.h>

//POSITION-------------------------------------------------------------------------------------------
void moveTo(float distance);
void end();
void editSpeed(unsigned int speed = 1);

//MOTEURS--------------------------------------------------------------------------------------------
// Configuration des broches pour le moteur X
#define X_STEP_PIN 3  // Broche STEP du moteur X
#define X_DIR_PIN 6   // Broche DIR du moteur X
#define ENABLE_PIN 8  // Broche ENABLE du moteur

#define M0_PIN 9   // Broche M0 du moteur X
#define M1_PIN 10  // Broche M1 du moteur X
#define M2_PIN 11  // Broche M2 du moteur X

// Configuration des paramètres des moteurs
#define MOTOR_STEPS 200  // Nombre de pas par tour du moteur
#define RPM 50           // Vitesse de rotation en tours par minute
#define MICROSTEPS 16    // Configuration du microstepping (1/16 de pas)

// Définition des objets AccelStepper pour le moteur X
AccelStepper stepperX(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);

//SETUP================================================================================================
void setup() {
  Serial.begin(9600);

  while (!Serial) {}
  Serial.println("[setup] Starting ascensor programm");

  // CONFIGURATION DES BROCHES DU MOTEUR X --------------------------------------------------------------
  pinMode(ENABLE_PIN, OUTPUT);

  // Configuration des paramètres du moteur X
  editSpeed(5);

  // Activation du driver pour le moteur X
  digitalWrite(ENABLE_PIN, LOW);  // Activer le driver du moteur X (LOW = activé)
}

//LOOP==================================================================================================
void loop() {
  Serial.println("[loop] starting moving");
  moveTo(100);  // Déplacer le moteur X sur 100 mm
  stepperX.runSpeedToPosition();  // Faire tourner le moteur à la vitesse spécifiée
}

//FONCTIONS================================================================================================
// Fonction pour faire avancer le moteur X sur une distance donnée en mm
void moveTo(float distance) {
  float distanceSteps = distance * MOTOR_STEPS * MICROSTEPS;  // Calcul du nombre de pas nécessaires
  stepperX.setCurrentPosition(0);  // Réinitialiser la position actuelle
  stepperX.moveTo(distanceSteps);  // Déplacer le moteur vers la position cible
}

void editSpeed(unsigned int speed = 1) {
  stepperX.setMaxSpeed((float(MOTOR_STEPS * MICROSTEPS) / 60) * RPM / speed);  // Définir la vitesse maximale
  stepperX.setAcceleration((float(MOTOR_STEPS * MICROSTEPS) / 60) * RPM / (speed * 4));  // Définir l'accélération
}
