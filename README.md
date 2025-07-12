# CPP_Pruefung_Sven_Flori

Da unsere game.cpp zwischenzeitlich an die 200 Zielen hatte ( wir haben über if-else-Abfragen beide Spielmode parallel implementiert), haben wir recherchiert und uns dazu entschieden, das Abstrakter zu machen mit Runtime-Polymorphismus. Das heißt wir behalten unsere Logik der Spielmodi in den Spielmodi Dateien aber machen ein GameModeInterface, welches an die Beiden Modi-Interfaces vererbt und die in dem wir das Interface des jeweiligen Spieles gestalten, in dem wir unsere Logiken aufrufen. Dies macht den code schlanker und effizienter und macht es auch einfach, neue Spielmodi zu implementieren

