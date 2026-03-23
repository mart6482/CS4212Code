#include <iostream>
#include "SceneContainer.h"
#include "SceneLoader.h"
#include "SceneParserJSON.h"

int main (int argc, char* argv[]){
    SceneContainer myScene;
    SceneLoader loader(myScene);
    SceneParser_JSON parser(std::make_shared<SceneLoader>(loader));

    std::string filename = argv[1];
    parser.parseFileData(filename);
}