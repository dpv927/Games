#include <raylib.h>
#define CAMERA_SPEED 1

int main(void) {
  
  // ---------------------- //
  // Creeper Body Variables // 
  // ---------------------- //
  Vector3 bodyPosition = {.x=0,.y=0,.z=0};
  Vector3 bodyDimensions = { 
    .x = 10, // Width 
    .y = 40, // Height
    .z = 20, // Width
  };

  // ---------------------- //
  // Creeper Head Variables // 
  // ---------------------- //
  Vector3 headDimensions = {
    .x = 20, // The head
    .y = 20, // Is a 
    .z = 20, // Big ass cube
  };
  Vector3 headPosition = {
    .x = 0, // Center X
    .y = bodyDimensions.y/2.0f + headDimensions.x/2.0f, // Center Y
    .z = 0, // Center Z
  };

  // ---------------------- //
  // Creeper Eyes Variables // 
  // ---------------------- //
  Vector3 eyesDimensions = {
    .x = 4,
    .y = 4,
    .z = 4,
  };
  Vector3 leftEyePosition = {
    .x = (headDimensions.x/2 - eyesDimensions.x/2)+0.5,
    .y = headDimensions.y/4 + headPosition.y,
    .z = headDimensions.z/4,
  };
  Vector3 rightEyePosition = {
    .x = leftEyePosition.x,
    .y = leftEyePosition.y,
    .z = -(headDimensions.z/4.0f),
  };

  // ---------------------- //
  // Creeper Mouth Variables // 
  // ---------------------- //
  Vector3 mouth1Dimensions = {
    .x = eyesDimensions.x,
    .y = eyesDimensions.y-2,
    .z = (leftEyePosition.z - rightEyePosition.z) - eyesDimensions.z,
  };
  Vector3 mouth1Position = {
    .x = leftEyePosition.x,
    .y = leftEyePosition.y - (mouth1Dimensions.y/2.0f + eyesDimensions.y/2.0f),
    .z = 0,
  };
  Vector3 mouth2Dimensions = {
    .x = mouth1Dimensions.x,
    .y = eyesDimensions.y * 3/4,
    .z = mouth1Dimensions.z + eyesDimensions.z,
  };
  Vector3 mouth2Position = {
    .x = mouth1Position.x,
    .y = mouth1Position.y - (mouth1Dimensions.y/2.0f + mouth2Dimensions.y/2.0f),
    .z = 0,
  };
  Vector3 mouth3Dimensions = {
    .x = mouth1Dimensions.x,
    .y = mouth2Dimensions.y,
    .z = (mouth2Dimensions.z - mouth1Dimensions.z)/2.0f,
  };
  Vector3 mouth3Position = {
    .x = mouth1Position.x,
    .y = mouth2Position.y - (mouth2Dimensions.y/2 + mouth3Dimensions.y/2.0f),
    .z = (mouth2Dimensions.z - mouth1Dimensions.z/2.0f)-3,
  };
  Vector3 mouth4Position = {
    .x = mouth1Position.x,
    .y = mouth2Position.y - (mouth2Dimensions.y/2 + mouth3Dimensions.y/2.0f),
    .z = -((mouth2Dimensions.z - mouth1Dimensions.z/2.0f)-3),
  };

  Vector3 legs1Dimensions = {
    .x = bodyDimensions.x*0.8f,
    .y = headDimensions.y/1.8f,
    .z = bodyDimensions.z,
  };
  Vector3 legs1Position = {
    .x = legs1Dimensions.x,
    .y = -bodyDimensions.y/2.0f - legs1Dimensions.y/2.0f,
    .z = bodyPosition.z
  };

  Vector3 legs2Dimensions = {
    .x = bodyDimensions.x*0.8f,
    .y = headDimensions.y/1.8f,
    .z = bodyDimensions.z,
  };
  Vector3 legs2Position = {
    .x = bodyPosition.x - legs1Dimensions.x,
    .y = -bodyDimensions.y/2.0f - legs1Dimensions.y/2.0f,
    .z = 0
  };

  /* 3D Camera */
  Camera3D camera = {
    .position = {54,2,49} ,
    .target = {0,0,0},
    .up = {0,1,0},
    .fovy = 89,
    .projection = CAMERA_PERSPECTIVE
  };
  
  InitWindow(800, 600, "3D graphics");
  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(0xffffffAA)); 

    DrawText(TextFormat("Position X: %i", (int)camera.position.x), 10, 10, 18, BLACK);
    DrawText(TextFormat("Position Y: %i", (int)camera.position.y), 10, 30, 18, BLACK);
    DrawText(TextFormat("Position Z: %i", (int)camera.position.z), 10, 50, 18, BLACK);
      
    if(IsKeyDown(KEY_DOWN)) 
      camera.position.y -= 1;
    else if(IsKeyDown(KEY_UP))
      camera.position.y += 1;
    else if(IsKeyDown(KEY_RIGHT))
      camera.position.z += 1;
    else if(IsKeyDown(KEY_LEFT))
      camera.position.z -= 1;
    else if(IsKeyDown(KEY_W))
      camera.position.x -= 1;
    else if(IsKeyDown(KEY_S))
      camera.position.x += 1;
    BeginMode3D(camera);

    // Draw the body 
    DrawCubeV(bodyPosition, bodyDimensions, GREEN);
    DrawCubeWiresV(bodyPosition, bodyDimensions, BLACK);

    // Draw the Head 
    DrawCubeV(headPosition, headDimensions, GREEN);
    DrawCubeWiresV(headPosition, headDimensions, BLACK);

    // Draw the eyes
    DrawCubeV(leftEyePosition, eyesDimensions, BLACK); // left eye
    DrawCubeV(rightEyePosition, eyesDimensions, BLACK); // right eye

    // Draw the mouth (4 parts)
    DrawCubeV(mouth1Position, mouth1Dimensions, BLACK); // Mouth1
    DrawCubeV(mouth2Position, mouth2Dimensions, BLACK); // Mouth2
    DrawCubeV(mouth3Position, mouth3Dimensions, BLACK); // Mouth3
    DrawCubeV(mouth4Position, mouth3Dimensions, BLACK); // Mouth4

    // Draw the legs
    DrawCubeV(legs1Position, legs1Dimensions, GREEN);
    DrawCubeWiresV(legs1Position, legs1Dimensions, BLACK);
    DrawCubeV(legs2Position, legs2Dimensions, GREEN);
    DrawCubeWiresV(legs2Position, legs2Dimensions, BLACK);
  
    EndMode3D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
