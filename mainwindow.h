/**
 * Description: header file for the Main Window of the Learn Mips application
 * Authors: Matthew Ashton Knochel, Carter Dean, Abdulla Alnuaimi, Logan Luker, Aidan Sheehan
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "model.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow constructor
     * @param parent parent widget
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief deconstructor for Main Window
     */
    ~MainWindow();

private:
    /**
     * @brief ui pointer to ui
     */
    Ui::MainWindow *ui;

    /**
     * @brief modelPtr pointer to the model for connecting signals/slots
     */
    Model* modelPtr;

    /**
     * @brief physObjBodies Stores physics QLabels with their id as the key
     */
    std::map<int, QLabel*> physObjLabels;

    /**
     * @brief closeEvent override of close event
     * @param event the event
     */
    void closeEvent (QCloseEvent *event);

signals:
    /**
     * @brief answerCurrentCodeRequest signal to send the current code in the editor
     */
    void answerCurrentCodeRequest(std::string);

    /**
     * @brief runRequest signal to run the code
     * @param code the user code to run
     * @param checkSolutionValidity determines if the solution should be checked or the code just run
     */
    void runRequest(QString code, bool checkSolutionValidity);

    /**
     * @brief requestTabVisibilities signal to trigger the model to push the updated visibilities of the tabs
     */
    void requestTabVisibilities();

private slots:
    /**
     * @brief runButtonClicked slot for when the run button is pressed
     */
    void runButtonClicked();
    /**
     * @brief submitButtonClicked slot for when the check solution button is clicked
     */
    void submitButtonClicked();

    /**
     * @brief currentCodeRequested slot to respond to  current code requests from the model
     */
    void currentCodeRequested();

    /**
     * @brief moveLabel Moves the physObj label with the specified id to the given x y relative to the window
     * @param id of the physicsObj label to move
     * @param x the horizontal component in pixels
     * @param y the vertical component in pixels
     */
    void moveLabel(int id, int x, int y);

    /**
     * @brief createPhysLabel creates a QLabel with physics at the given x y coordinate
     * @param x the horizontal component in pixels
     * @param y the vertical component in pixels
     */
    void createPhysLabel(int id, int x, int y);

    /**
     * @brief deletePhysLabel Deletes the physics label with the given id.
     * @param id of the physicsObj to be deleted.
     */
    void deletePhysLabel(int id);

    /**
     * @brief updateConsole slot to update the text of the console to text
     * @param text the new console text
     */
    void updateConsole(QString text);

    /**
     * @brief updateCheckBox slot to set a section as completed visually
     * @param ID id of section to complete
     * @param checked whether to check or uncheck the section
     */
    void updateCheckBox(int ID, bool checked);

    /**
     * @brief displayReferenceWindow slot to display the reference list window
     */
    void displayReferenceWindow();
};
#endif // MAINWINDOW_H
