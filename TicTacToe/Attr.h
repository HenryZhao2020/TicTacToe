#pragma once

/**
 * @brief Contains shared attributes in the program.
 */
class Attr {
public:
    // Game Progress
    /**
     * @brief Index locations of the 'X' squares.
     */
    QList<int> xPlaced;
    /**
     * @brief Index locations of the 'O' squares.
     */
    QList<int> oPlaced;
    /**
     * @brief Whether it is X's turn to place its mark.
     */
    bool xTurn;
    /**
     * @brief Whether the current round has ended.
     */
    bool ended;

    // Settings
    /**
     * @brief Whether the player is playing against AI.
     */
    bool playAI;
    /**
     * @brief Whether animations are enabled.
     */
    bool animated;
    /**
     * @brief Whether the hint on the left of the game bar is visible.
     */
    bool hinted;

    // Statistics
    /**
     * @brief Total number of wins that 'X' has.
     */
    int xWins;
    /**
     * @brief Total number of wins that 'O' has.
     */
    int oWins;
    /**
     * @brief Total number of ties between 'X' and 'O'.
     */
    int ties;

    // Calculated properties based on the existing attributes
    /**
     * @brief Returns the total number of gameplays.
     * @return Total number of gameplays.
     */
    int getTotalPlays();

    // Reset attributes
    /**
     * @brief Resets the game progress.
     */
    void resetProgress();
    /**
     * @brief Resets all settings to their default values.
     */
    void resetSettings();
    /**
     * @brief Resets all statistics to zero.
     */
    void resetStats();

    // Save & Load
    /**
     * @brief Saves all attributes to the local disk.
     */
    void save();
    /**
     * @brief Loads all attributes from the local disk.
     * @return 'true' if successful; 'false' otherwise.
     */
    bool load();

    // Singleton access
    /**
     * @brief Provides access to the singleton instance.
     * @return The singleton instance.
     */
    static Attr &get();

private:
    // Private constructor to prevent external instantiation
    Attr();
    ~Attr();
};
