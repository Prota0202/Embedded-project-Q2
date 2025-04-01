#include "Motors.h"
#include "Sensors.h"
#include "PID.h"
#include <Arduino.h>

// Pins
#define IR_LEFT A2
#define IR_RIGHT A1
#define IR_CLIFF A0
#define TRIGGER_PIN1 9
#define ECHO_PIN1 10
#define TRIGGER_PIN2 6
#define ECHO_PIN2 7
#define SERVO_PIN 3

Motors motors;
Sensors sensors(IR_LEFT, IR_RIGHT, IR_CLIFF, TRIGGER_PIN1, ECHO_PIN1, TRIGGER_PIN2, ECHO_PIN2, SERVO_PIN);
PID pidController(1.5, 0.0, 0.5);

const int obstacleThreshold = 7;
const int cliffThreshold = 600;
const int motorSpeed = 25;
const int motorSpeed2 = 100;
const int turnSpeed = 25;
const int turnDuration = 1500; // 1,5 seconde pour chaque virage à angle droit
const int turnDuration2 = 1200;

// Variable pour vérifier si le robot est arrêté définitivement
bool isStopped = false;

// Variables pour gérer le temps de fonctionnement
unsigned long startTime;
const unsigned long maxRunTime = 10000; // 10 secondes en millisecondes

void setup() {
    Serial.begin(9600);
    
    // Délai de démarrage de 2 secondes
    delay(2000);
    
    motors.init(); // ⚠️ C'est là qu'on initialise proprement
    Serial.println("Robot prêt");
    
    // Enregistrer le temps de démarrage
    startTime = millis();
}

// Nouvelle fonction pour contourner un obstacle avec quatre virages à angle droit
void avoidObstacle() {
    // Vérifier d'abord si le temps maximal est presque atteint
    if (millis() - startTime >= maxRunTime - 1000) {  // Si moins d'une seconde reste
        Serial.println("Temps presque écoulé, arrêt pendant manœuvre d'évitement");
        motors.stop();
        isStopped = true;
        return;
    }
    
    Serial.println("Contournement d'obstacle");
    
    // Arrêter d'abord
    motors.stop();
    delay(200);
    
    // 1er virage : Tourner à droite à angle droit
    Serial.println("1er virage: angle droit à droite");
    motors.right(turnSpeed);
    delay(turnDuration2); // 1,2 seconde
    motors.stop();
    delay(200);
    
    // Vérifier le temps après chaque mouvement important
    if (millis() - startTime >= maxRunTime) {
        Serial.println("Temps de fonctionnement maximal atteint pendant manœuvre");
        motors.stop();
        isStopped = true;
        return;
    }
    
    // Avancer un peu
    motors.forward(motorSpeed2);
    delay(1000);
    motors.stop();
    delay(200);
    
    // Vérifier le temps à nouveau
    if (millis() - startTime >= maxRunTime) {
        Serial.println("Temps de fonctionnement maximal atteint pendant manœuvre");
        motors.stop();
        isStopped = true;
        return;
    }
    
    // 2ème virage : Tourner à gauche à angle droit
    Serial.println("2ème virage: angle droit à gauche");
    motors.left(turnSpeed);
    delay(turnDuration); // 1,5 seconde
    motors.stop();
    delay(200);
    
    // Vérifier le temps à nouveau
    if (millis() - startTime >= maxRunTime) {
        Serial.println("Temps de fonctionnement maximal atteint pendant manœuvre");
        motors.stop();
        isStopped = true;
        return;
    }
    
    // Avancer un peu
    motors.forward(motorSpeed2);
    delay(1000);
    motors.stop();
    delay(200);
    
    // Vérifier le temps à nouveau
    if (millis() - startTime >= maxRunTime) {
        Serial.println("Temps de fonctionnement maximal atteint pendant manœuvre");
        motors.stop();
        isStopped = true;
        return;
    }
    
    // 3ème virage : Tourner à gauche à angle droit
    Serial.println("3ème virage: angle droit à gauche");
    motors.left(turnSpeed);
    delay(turnDuration); // 1,5 seconde
    motors.stop();
    delay(200);
    
    // Vérifier le temps à nouveau
    if (millis() - startTime >= maxRunTime) {
        Serial.println("Temps de fonctionnement maximal atteint pendant manœuvre");
        motors.stop();
        isStopped = true;
        return;
    }
    
    // Avancer un peu
    motors.forward(motorSpeed2);
    delay(1000);
    motors.stop();
    delay(200);
    
    // Vérifier le temps à nouveau
    if (millis() - startTime >= maxRunTime) {
        Serial.println("Temps de fonctionnement maximal atteint pendant manœuvre");
        motors.stop();
        isStopped = true;
        return;
    }
    
    // 4ème virage : Tourner à droite à angle droit
    Serial.println("4ème virage: angle droit à droite");
    motors.right(turnSpeed);
    delay(turnDuration); // 1,5 seconde
    motors.stop();
    delay(200);
    
    // Vérifier le temps une dernière fois avant de reprendre le mouvement normal
    if (millis() - startTime >= maxRunTime) {
        Serial.println("Temps de fonctionnement maximal atteint pendant manœuvre");
        motors.stop();
        isStopped = true;
        return;
    }

    // Reprendre le mouvement normal si le temps le permet
    motors.forward(motorSpeed2);
}

void loop() {
    // Si le robot est arrêté définitivement, on sort de la boucle
    if (isStopped) {
        return;
    }
    
    // Vérifier si le temps de fonctionnement maximal est atteint
    if (millis() - startTime >= maxRunTime) {
        Serial.println("Temps de fonctionnement maximal atteint");
        motors.stop();
        isStopped = true;
        return;
    }

    int distance1 = sensors.readDistance1();
    int distance2 = sensors.readDistance2();
    int cliffValue = sensors.readIRCliff();

    // Si un obstacle est détecté par l'un des capteurs ultrason
    if ((distance1 > 0 && distance1 <= obstacleThreshold) || 
        (distance2 > 0 && distance2 <= obstacleThreshold)) {
        Serial.println("Obstacle détecté");
        motors.stop();
        avoidObstacle(); // Appeler la fonction pour contourner l'obstacle
        return;
    }

    // Si un vide est détecté
    if (cliffValue > cliffThreshold) {
        Serial.println("Vide détecté");
        motors.stop();   // Arrêt immédiat des moteurs
        isStopped = true; // Marque le robot comme arrêté définitivement
        return;           // Sort de la boucle
    }

    // Code pour ajuster les moteurs avec PID
    int valueLeft = sensors.readIRLeft();
    int valueRight = sensors.readIRRight();
    float correction = pidController.compute(valueRight - valueLeft);

    int speedLeft = constrain(150 - correction, 0, 50);
    int speedRight = constrain(150 + correction, 0, 50);

    motors.forward();  // Commence à avancer
    motors.motorLEFT->setSpeed(speedLeft);   // Régle la vitesse du moteur gauche
    motors.motorRIGHT->setSpeed(speedRight); // Régle la vitesse du moteur droit

    delay(10);
}