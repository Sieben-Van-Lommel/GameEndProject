#include "characterController.h"
#include "TestChar.c"        // Contains your sprite data (TileLabel, etc.)
//

// Global player position
UINT8 playerX = 88;
UINT8 playerY = 78;

// --- Position History ---
// Record the player's position every 100ms.
// With HISTORY_SIZE 100, this stores roughly 10 seconds of positions.
#define HISTORY_SIZE 100
UINT8 posHistoryX[HISTORY_SIZE];
UINT8 posHistoryY[HISTORY_SIZE];
UINT8 historyIndex = 0;

// Count how many updates have occurred
UINT16 updateCount = 0;

// Original player control function (unchanged)
void characterController() {
    UINT8 currentspriteindex = 0;

    // Initialize player sprite (sprite slot 0)
    set_sprite_data(0, 2, TestChar);
    set_sprite_tile(0, 0);
    move_sprite(0, playerX, playerY);
    SHOW_SPRITES;

    while(1) {
        // Process input and update player's absolute position
        switch(joypad()){
            case J_LEFT: 
                scroll_sprite(0, -1, 0);
                playerX--;  // update absolute position
                break;
            case J_RIGHT: 
                scroll_sprite(0, 1, 0);
                playerX++;
                break;  
            case J_UP: 
                scroll_sprite(0, 0, -1);
                playerY--;
                break; 
            case J_DOWN: 
                scroll_sprite(0, 0, 1);
                playerY++;
                break;                                                   
        }
        
        // Update player's sprite position
        move_sprite(0, playerX, playerY);

        // Record current position into the history buffer
        posHistoryX[historyIndex] = playerX;
        posHistoryY[historyIndex] = playerY;
        
        // Advance the circular buffer and count updates
        historyIndex = (historyIndex + 1) % HISTORY_SIZE;
        updateCount++;

        // If the history buffer has wrapped around and at least 10 seconds have passed, spawn a ghost.
        if(historyIndex == 0 && updateCount >= HISTORY_SIZE) {
            spawnGhostSprite();
        }
        
        delay(100);  // roughly 100ms per update (~10 sec for 100 entries)
    }
}

// New function: spawnGhostSprite()
// Spawns a ghost sprite (using sprite slot 1) at the position where the player was 10 seconds ago.
void spawnGhostSprite() {
    // The current historyIndex now holds the oldest recorded position (from 10 seconds ago)
    UINT8 ghostX = posHistoryX[historyIndex];
    UINT8 ghostY = posHistoryY[historyIndex];

    // Set up the ghost sprite on sprite slot 1.
    // Use the same tile as the player (adjust if needed)
    set_sprite_tile(1, 0);
    move_sprite(1, ghostX, ghostY);
    SHOW_SPRITES;
}
