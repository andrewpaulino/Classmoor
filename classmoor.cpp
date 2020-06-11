#include "classmoor.h"

bool Classmoor::isFirstTimeRunning() {
    QString pathToUserDataFile = "user_data.txt";
    QFileInfo check_file(pathToUserDataFile);
       if (check_file.exists()) {
           return false;
       }
           return true;
}
