#include "CGhost.hpp"

#pragma once

/**
 * @class CGhost_3
 * @brief A class representing another specific type of ghost in the game - Clyde.
 *
 * This class extends the base CGhost class and implements the behavior of another type of ghost.
 */
class CGhost_3 : public CGhost {
	public:
		/**
		 * @brief Default constructor for CGhost_3.
		 * @param entityLook Integer defining the number of coloring for the entity
		 */
		CGhost_3(int entityLook);

	protected:
		/**	
		 * @brief Overrides the base class's decideMoveDirection method to move towards the player based on his relative possition. 
		 * @param gameMap The game map.
		 * @param player The player entity.
		 * 
		 * This method determines the next move direction for the ghost based on the relative position of the player.
		 * The ghost directly moves towards the player along the vertical or horizontal axis.
		 * Also handles the case when the position remains the same by making a random move, so that the ghost doesn't just stand on one place.
		 */
		virtual void decideMoveDirection(CMap& gameMap, const CEntity& player) override;

	private:

};