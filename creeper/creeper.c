#include <raylib.h>
#define CAMERA_SPEED 1

int main(void) {
  
  // ---------------------- //
  // Creeper Body Variables // 
  // ---------------------- //
  Vector3 bodyPosition = {.x=0,.y=0,.z=0};
  Vector3 bodyDimensions = { 
    .x = 12, // Width 
    .y = 40, // Height
    .z = 12, // Width
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

  /* 3D Camera */
  Camera3D camera = {
    .position = {bodyDimensions.y,0,0} ,
    .target = {0,0,0},
    .up = {0,1,0},
    .fovy = 89,
    .projection = CAMERA_PERSPECTIVE
  };

  
  InitWindow(800, 600, "3D graphics");
  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(0x181818AA));
      
    if(IsKeyDown(KEY_DOWN)) 
      camera.position.y -= 1;
    else if(IsKeyDown(KEY_UP))
      camera.position.y += 1;
    else if(IsKeyDown(KEY_RIGHT))
      camera.position.x += 1;
    else if(IsKeyDown(KEY_LEFT))
      camera.position.x -= 1;
    else if(IsKeyDown(KEY_W))
      camera.position.z -= 1;
    else if(IsKeyDown(KEY_S))
      camera.position.z += 1;
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

    EndMode3D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
