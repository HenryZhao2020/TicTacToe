#pragma once

// Forward declarations
class Game;

/**
 * @brief Displays a hint on the left and a set of buttons on the right.
 */
class GameBar : public QFrame {
    Q_OBJECT

public:
    /**
     * @brief Initializes a new 'GameBar' instance.
     * @param game The parent 'Game' instance.
     */
    GameBar(Game *game);
    ~GameBar();

    /**
     * @brief Sets the hint icon on the left.
     * @param icon The icon to be displayed.
     */
    void setHintIcon(const QIcon &icon);

    /**
     * @brief Sets the hint text beside the icon.
     * @param text The text to be displayed.
     */
    void setHintText(const QString &text);

    /**
     * @brief Shows or hides the hint icon and text.
     * @param visible The visibility of the hint.
     */
    void setHintVisible(bool visible);

    /**
     * @brief Shows or hides the 'Restart' button.
     * @param visible The visibility of the 'Restart' button.
     */
    void setRestartVisible(bool visible);

private:
    QHBoxLayout *barLayout;
    QPushButton *iconButton;
    QLabel *hintLabel;
    QPushButton *restartButton;

    // Used for the typewriting effect
    QTimer *hintTimer = nullptr;
    // Store the displayed length of the hint text
    int hintLength;

    /**
     * @brief Displays the subsequent character after each interval,
     * simulating the interface of a typewriter.
     * @param text The text to be displayed.
     */
    void typewriteHint(const QString &text);

    /**
     * @brief Creates a new button on the right.
     * @param icon The icon of the button.
     * @param tip The tool tip of the button.
     * @param callable The action of the button on click.
     * @return The created button.
     */
    template <typename Callable>
    QPushButton *newButton(const QIcon &icon, const QString &tip,
                           const Callable &callable);
};
