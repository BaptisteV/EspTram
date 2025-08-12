## Description
Client de l'API [DiviaApi](https://github.com/BaptisteV/DiviaApi)
Affiche le prochain tram de la station Foch Gare à Dijon sur un afficheur à segments TM1637. S'exécute sur un module ESP32

<img src="https://abacasstorageaccnt.blob.core.windows.net/cirkit/14afd62b-f20a-4c63-b241-d83df4a59343.png" alt="TM1637" width="150"/>
<img src="https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32/_images/esp32-DevKitM-1-isometric.png" alt="ESP32" width="150"/>

## Fonctionnalité
Toutes les secondes, récupère les horaires de l'API [DiviaApi](https://github.com/BaptisteV/DiviaApi). Affiche l'horaire du prochain tram sur l'afficheur à segments.
L'API renvoi deux horaires. Si le tram est déjà passé, on affiche le prochain. On affiche des underscore quand le prochain tram est dans plus de 99 minutes (typiquement le soir).

## Installation
Créer le fichier ***src/Config.cpp***
```cpp
#define WIFI_SSID "YourSSID"
#define WIFI_PASSWORD "YourPassword"
#define DIVIA_API_URL "http://YourApiHostname:YourApiPort/api/v1/foch"
```

Installer [PlateformIO](https://docs.platformio.org/en/latest/core/installation/index.html)

## Execution
```bash
plateformio run
```

## Dépendences
- [PlateformIO](https://platformio.org/) pour gérer le projet
- [ArduinoJson](https://arduinojson.org/) pour désérialiser les réponses de l'API
- [TM1637](https://registry.platformio.org/libraries/smougenot/TM1637) pour l'affichage