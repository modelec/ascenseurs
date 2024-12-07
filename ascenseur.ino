 #include <AccelStepper.h>


  // Configuration des broches pour le moteur X
  #define STEP_PIN 2  // Broche STEP du moteur X
  #define DIR_PIN 5   // Broche DIR du moteur X
  #define ENABLE_PIN 8  // Broche ENABLE du moteur

  // Créer une instance de la classe AccelStepper
  AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

  void setup() {
    pinMode(ENABLE_PIN, OUTPUT);
    digitalWrite(ENABLE_PIN, LOW); 
    // Configurer la vitesse et l'accélération
    stepper.setMaxSpeed(1000000);   // Vitesse maximale (steps par seconde)
    stepper.setAcceleration(50000); // Accélération (steps par seconde^2)

    // Initialisation du mouvement
    Serial.begin(9600);
    Serial.println("Moteur prêt");
  }

  void loop() {
    // Déplacer vers une position spécifique
    stepper.moveTo(100000);  // Aller à 1000 pas
    stepper.runToPosition(); // Attendre d'arriver à la position

    delay(1000); // Pause d'une seconde

    stepper.moveTo(-100000);  // Retour à la position d'origine
    stepper.runToPosition();

    delay(1000); // Pause d'une seconde
  }
