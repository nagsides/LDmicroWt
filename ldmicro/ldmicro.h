#ifndef __LDMICRO_H
#define __LDMICRO_H

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WText.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WAbstractItemModel.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WString.h>
#include <Wt/WStandardItem.h>
#include <Wt/WFlags.h>
#include <Wt/WStandardItem.h>
#include <vector>
#include <memory>

#include "wttypes.h"
#include "maincontrols.h"
#include "draw_outputdev.h"
#include "portable.h"

//-----------------------------------------------
// Constants for the GUI. We have drop-down menus, a listview for the I/Os,
// etc.

#define NUM_SUPPORTED_MCUS  16
#define IO_COLUMN_COUNT     5

// Size of the font that we will use to draw the ladder diagrams, in pixels
#define FONT_WIDTH   8
#define FONT_HEIGHT 16

// Menu IDs
#define MNU_NEW                 0x01
#define MNU_OPEN                0x02
#define MNU_SAVE                0x03
#define MNU_SAVE_AS             0x04
#define MNU_EXPORT              0x05
#define MNU_EXIT                0x06

#define MNU_UNDO                0x10
#define MNU_REDO                0x11
#define MNU_PUSH_RUNG_UP        0x12
#define MNU_PUSH_RUNG_DOWN      0x13
#define MNU_INSERT_RUNG_BEFORE  0x14
#define MNU_INSERT_RUNG_AFTER   0x15
#define MNU_DELETE_ELEMENT      0x16
#define MNU_DELETE_RUNG         0x17

#define MNU_INSERT_COMMENT      0x20
#define MNU_INSERT_CONTACTS     0x21
#define MNU_INSERT_COIL         0x22
#define MNU_INSERT_TON          0x23
#define MNU_INSERT_TOF          0x24
#define MNU_INSERT_RTO          0x25
#define MNU_INSERT_RES          0x26
#define MNU_INSERT_OSR          0x27
#define MNU_INSERT_OSF          0x28
#define MNU_INSERT_CTU          0x29
#define MNU_INSERT_CTD          0x2a
#define MNU_INSERT_CTC          0x2b
#define MNU_INSERT_ADD          0x2c
#define MNU_INSERT_SUB          0x2d
#define MNU_INSERT_MUL          0x2e
#define MNU_INSERT_DIV          0x2f
#define MNU_INSERT_MOV          0x30
#define MNU_INSERT_READ_ADC     0x31
#define MNU_INSERT_SET_PWM      0x32
#define MNU_INSERT_UART_SEND    0x33
#define MNU_INSERT_UART_RECV    0x34
#define MNU_INSERT_EQU          0x35
#define MNU_INSERT_NEQ          0x36
#define MNU_INSERT_GRT          0x37
#define MNU_INSERT_GEQ          0x38
#define MNU_INSERT_LES          0x39
#define MNU_INSERT_LEQ          0x3a
#define MNU_INSERT_OPEN         0x3b
#define MNU_INSERT_SHORT        0x3c
#define MNU_INSERT_MASTER_RLY   0x3d
#define MNU_INSERT_SHIFT_REG    0x3e
#define MNU_INSERT_LUT          0x3f
#define MNU_INSERT_FMTD_STR     0x40
#define MNU_INSERT_PERSIST      0x41
#define MNU_MAKE_NORMAL         0x42
#define MNU_NEGATE              0x43
#define MNU_MAKE_SET_ONLY       0x44
#define MNU_MAKE_RESET_ONLY     0x45
#define MNU_INSERT_PWL          0x46

#define MNU_MCU_SETTINGS        0x50
#define MNU_PROCESSOR_0         0xa0

#define MNU_SIMULATION_MODE     0x60
#define MNU_START_SIMULATION    0x61
#define MNU_STOP_SIMULATION     0x62
#define MNU_SINGLE_CYCLE        0x63

#define MNU_COMPILE             0x70
#define MNU_COMPILE_AS          0x71

#define MNU_MANUAL              0x80
#define MNU_ABOUT               0x81

// #define MNU_ADV_SIMULATION

// New menu items here

// extern QActionGroup* ProcessorMenuGroup;

// extern HWID PinList;

// extern HMENU MNU_ADV_SIMULATION;

// Columns within the I/O etc. listview.
#define LV_IO_NAME              0x00
#define LV_IO_TYPE              0x01
#define LV_IO_STATE             0x02
#define LV_IO_PIN               0x03
#define LV_IO_PORT              0x04
//-----------------------------------------------
// Data structures for the actual ladder logic. A rung on the ladder
// is a series subcircuit. A series subcircuit contains elements or
// parallel subcircuits. A parallel subcircuit contains elements or series
// subcircuits. An element is a set of contacts (possibly negated) or a coil.

#define MAX_ELEMENTS_IN_SUBCKT  16

#define ELEM_PLACEHOLDER        0x01
#define ELEM_SERIES_SUBCKT      0x02
#define ELEM_PARALLEL_SUBCKT    0x03
#define ELEM_PADDING            0x04
#define ELEM_COMMENT            0x05

#define ELEM_CONTACTS           0x10
#define ELEM_COIL               0x11
#define ELEM_TON                0x12
#define ELEM_TOF                0x13
#define ELEM_RTO                0x14
#define ELEM_RES                0x15
#define ELEM_ONE_SHOT_RISING    0x16
#define ELEM_ONE_SHOT_FALLING   0x17
#define ELEM_MOVE               0x18
#define ELEM_ADD                0x19
#define ELEM_SUB                0x1a
#define ELEM_MUL                0x1b
#define ELEM_DIV                0x1c
#define ELEM_EQU                0x1d
#define ELEM_NEQ                0x1e
#define ELEM_GRT                0x1f
#define ELEM_GEQ                0x20
#define ELEM_LES                0x21
#define ELEM_LEQ                0x22
#define ELEM_CTU                0x23
#define ELEM_CTD                0x24
#define ELEM_CTC                0x25
#define ELEM_SHORT              0x26
#define ELEM_OPEN               0x27
#define ELEM_READ_ADC           0x28
#define ELEM_SET_PWM            0x29
#define ELEM_UART_RECV          0x2a
#define ELEM_UART_SEND          0x2b
#define ELEM_MASTER_RELAY       0x2c
#define ELEM_SHIFT_REGISTER     0x2d
#define ELEM_LOOK_UP_TABLE      0x2e
#define ELEM_FORMATTED_STRING   0x2f
#define ELEM_PERSIST            0x30
#define ELEM_PIECEWISE_LINEAR   0x31

#define CASE_LEAF \
        case ELEM_PLACEHOLDER: \
        case ELEM_COMMENT: \
        case ELEM_COIL: \
        case ELEM_CONTACTS: \
        case ELEM_TON: \
        case ELEM_TOF: \
        case ELEM_RTO: \
        case ELEM_CTD: \
        case ELEM_CTU: \
        case ELEM_CTC: \
        case ELEM_RES: \
        case ELEM_ONE_SHOT_RISING: \
        case ELEM_ONE_SHOT_FALLING: \
        case ELEM_EQU: \
        case ELEM_NEQ: \
        case ELEM_GRT: \
        case ELEM_GEQ: \
        case ELEM_LES: \
        case ELEM_LEQ: \
        case ELEM_ADD: \
        case ELEM_SUB: \
        case ELEM_MUL: \
        case ELEM_DIV: \
        case ELEM_MOVE: \
        case ELEM_SHORT: \
        case ELEM_OPEN: \
        case ELEM_READ_ADC: \
        case ELEM_SET_PWM: \
        case ELEM_UART_SEND: \
        case ELEM_UART_RECV: \
        case ELEM_MASTER_RELAY: \
        case ELEM_SHIFT_REGISTER: \
        case ELEM_LOOK_UP_TABLE: \
        case ELEM_PIECEWISE_LINEAR: \
        case ELEM_FORMATTED_STRING: \
        case ELEM_PERSIST:

#define MAX_NAME_LEN                128
#define MAX_COMMENT_LEN             384
#define MAX_LOOK_UP_TABLE_LEN        60

typedef struct ElemSubckParallelTag ElemSubcktParallel;

typedef struct ElemCommentTag {
    char    str[MAX_COMMENT_LEN];
} ElemComment;

typedef struct ElemContactsTag {
    char    name[MAX_NAME_LEN];
    BOOL    negated;
} ElemContacts;

typedef struct ElemCoilTag {
    char    name[MAX_NAME_LEN];
    BOOL    negated;
    BOOL    setOnly;
    BOOL    resetOnly;
} ElemCoil;

typedef struct ElemTimeTag {
    char    name[MAX_NAME_LEN];
    int     delay;
} ElemTimer;

typedef struct ElemResetTag {
    char    name[MAX_NAME_LEN];
} ElemReset;

typedef struct ElemMoveTag {
    char    src[MAX_NAME_LEN];
    char    dest[MAX_NAME_LEN];
} ElemMove;

typedef struct ElemMathTag {
    char    op1[MAX_NAME_LEN];
    char    op2[MAX_NAME_LEN];
    char    dest[MAX_NAME_LEN];
} ElemMath;

typedef struct ElemCmpTag {
    char    op1[MAX_NAME_LEN];
    char    op2[MAX_NAME_LEN];
} ElemCmp;

typedef struct ElemCounterTag {
    char    name[MAX_NAME_LEN];
    int     max;
} ElemCounter;

typedef struct ElemReadAdcTag {
    char    name[MAX_NAME_LEN];
} ElemReadAdc;

typedef struct ElemSetPwmTag {
    char    name[MAX_NAME_LEN];
    int     targetFreq;
} ElemSetPwm;

typedef struct ElemUartTag {
    char    name[MAX_NAME_LEN];
} ElemUart;

typedef struct ElemShiftRegisterTag {
    char    name[MAX_NAME_LEN];
    int     stages;
} ElemShiftRegister;

typedef struct ElemLookUpTableTag {
    char    dest[MAX_NAME_LEN];
    char    index[MAX_NAME_LEN];
    int     count;
    BOOL    editAsString;
    SWORD   vals[MAX_LOOK_UP_TABLE_LEN];
} ElemLookUpTable;

typedef struct ElemPiecewiseLinearTag {
    char    dest[MAX_NAME_LEN];
    char    index[MAX_NAME_LEN];
    int     count;
    SWORD   vals[MAX_LOOK_UP_TABLE_LEN];
} ElemPiecewiseLinear;

typedef struct ElemFormattedStringTag {
    char    var[MAX_NAME_LEN];
    char    string[MAX_LOOK_UP_TABLE_LEN];
} ElemFormattedString;

typedef struct ElemPerisistTag {
    char    var[MAX_NAME_LEN];
} ElemPersist;

#define SELECTED_NONE       0
#define SELECTED_ABOVE      1
#define SELECTED_BELOW      2
#define SELECTED_RIGHT      3
#define SELECTED_LEFT       4
typedef struct ElemLeafTag {
    int     selectedState;
    BOOL    poweredAfter;
    union {
        ElemComment         comment;
        ElemContacts        contacts;
        ElemCoil            coil;
        ElemTimer           timer;
        ElemReset           reset;
        ElemMove            move;
        ElemMath            math;
        ElemCmp             cmp;
        ElemCounter         counter;
        ElemReadAdc         readAdc;
        ElemSetPwmTag       setPwm;
        ElemUart            uart;
        ElemShiftRegister   shiftRegister;
        ElemFormattedString fmtdStr;
        ElemLookUpTable     lookUpTable;
        ElemPiecewiseLinear piecewiseLinear;
        ElemPersist         persist;
    }       d;
} ElemLeaf;

typedef struct ElemSubcktSeriesTag {
    struct {
        int     which;
        union {
            void                   *any;
            ElemSubcktParallel     *parallel;
            ElemLeaf               *leaf;
        } d;
    } contents[MAX_ELEMENTS_IN_SUBCKT];
    int count;
} ElemSubcktSeries;

typedef struct ElemSubckParallelTag {
    struct {
        int     which;
        union {
            void                   *any;
            ElemSubcktSeries       *series;
            ElemLeaf               *leaf;
        } d;
    } contents[MAX_ELEMENTS_IN_SUBCKT];
    int count;
} ElemSubcktParallel;

typedef struct McuIoInfoTag McuIoInfo;

typedef struct PlcProgramSingleIoTag {
    char        name[MAX_NAME_LEN];
#define IO_TYPE_PENDING         0

#define IO_TYPE_DIG_INPUT       1
#define IO_TYPE_DIG_OUTPUT      2
#define IO_TYPE_READ_ADC        3
#define IO_TYPE_UART_TX         4
#define IO_TYPE_UART_RX         5
#define IO_TYPE_PWM_OUTPUT      6
#define IO_TYPE_INTERNAL_RELAY  7
#define IO_TYPE_TON             8
#define IO_TYPE_TOF             9
#define IO_TYPE_RTO             10
#define IO_TYPE_COUNTER         11
#define IO_TYPE_GENERAL         12
    int         type;
#define NO_PIN_ASSIGNED         0
    int         pin;
} PlcProgramSingleIo;

#define MAX_IO  512
typedef struct PlcProgramTag {
    struct {
        PlcProgramSingleIo  assignment[MAX_IO];
        int                 count;
    }           io;
    McuIoInfo  *mcu;
    int         cycleTime;
    int         mcuClock;
    int         baudRate;

#define MAX_RUNGS 99
    ElemSubcktSeries *rungs[MAX_RUNGS];
    BOOL              rungPowered[MAX_RUNGS];
    int               numRungs;
} PlcProgram;

extern void (*DrawChars)(HCRDC Hcr, int, int, const char *);


#define DISPLAY_MATRIX_X_SIZE 16
#define DISPLAY_MATRIX_Y_SIZE 512
extern ElemLeaf *DisplayMatrix[DISPLAY_MATRIX_X_SIZE][DISPLAY_MATRIX_Y_SIZE];
extern int DisplayMatrixWhich[DISPLAY_MATRIX_X_SIZE][DISPLAY_MATRIX_Y_SIZE];
extern ElemLeaf DisplayMatrixFiller;
#define PADDING_IN_DISPLAY_MATRIX (&DisplayMatrixFiller)
#define VALID_LEAF(x) ((x) != NULL && (x) != PADDING_IN_DISPLAY_MATRIX)
extern ElemLeaf *Selected;

//-----------------------------------------------
// For actually drawing the ladder logic on screen; constants that determine
// how the boxes are laid out in the window, need to know that lots of
// places for figuring out if a mouse click is in a box etc.

// dimensions, in characters, of the area reserved for 1 leaf element
#define POS_WIDTH   17
#define POS_HEIGHT  3

// offset from the top left of the window at which we start drawing, in pixels
#define X_PADDING    35
#define Y_PADDING    14

typedef struct PlcCursorTag {
    int left;
    int top;
    int width;
    int height;
} PlcCursor;

//-----------------------------------------------
// The syntax highlighting style colours; a structure for the palette.

typedef struct SyntaxHighlightingColoursTag {
    COLORREF    bg;             // background
    COLORREF    def;            // default foreground
    COLORREF    selected;       // selected element
    COLORREF    op;             // `op code' (like OSR, OSF, ADD, ...)
    COLORREF    punct;          // punctuation, like square or curly braces
    COLORREF    lit;            // a literal number
    COLORREF    name;           // the name of an item
    COLORREF    rungNum;        // rung numbers
    COLORREF    comment;        // user-written comment text

    COLORREF    bus;            // the `bus' at the right and left of screen

    COLORREF    simBg;          // background, simulation mode
    COLORREF    simRungNum;     // rung number, simulation mode
    COLORREF    simOff;         // de-energized element, simulation mode
    COLORREF    simOn;          // energzied element, simulation mode
    COLORREF    simBusLeft;     // the `bus,' can be different colours for
    COLORREF    simBusRight;    // right and left of the screen
} SyntaxHighlightingColours;
extern SyntaxHighlightingColours HighlightColours;

//-----------------------------------------------
// Processor definitions. These tables tell us where to find the I/Os on
// a processor, what bit in what register goes with what pin, etc. There
// is one master SupportedMcus table, which contains entries for each
// supported microcontroller.

typedef struct McuIoPinInfoTag {
    char    port;
    int     bit;
    int     pin;
} McuIoPinInfo;

typedef struct McuAdcPinInfoTag {
    int     pin;
    BYTE    muxRegValue;
} McuAdcPinInfo;

#define ISA_AVR             0x00
#define ISA_PIC16           0x01
#define ISA_ANSIC           0x02
#define ISA_INTERPRETED     0x03
#define ISA_ARDUINO         0x04

#define MAX_IO_PORTS        10
#define MAX_RAM_SECTIONS    5

typedef struct McuIoInfoTag {
    char            *mcuName;
    char             portPrefix;
    DWORD            inputRegs[MAX_IO_PORTS];         // a is 0, j is 9
    DWORD            outputRegs[MAX_IO_PORTS];
    DWORD            dirRegs[MAX_IO_PORTS];
    DWORD            flashWords;
    struct {
        DWORD            start;
        int              len;
    }                ram[MAX_RAM_SECTIONS];
    McuIoPinInfo    *pinInfo;
    int              pinCount;
    McuAdcPinInfo   *adcInfo;
    int              adcCount;
    int              adcMax;
    struct {
        int             rxPin;
        int             txPin;
    }                uartNeeds;
    int              pwmNeedsPin;
    int              whichIsa;
    BOOL             avrUseIjmp;
    DWORD            configurationWord;
} McuIoInfo;

//-----------------------------------------------
// Function prototypes

// ldmicro.cpp
void ProgramChanged(void);

void SetMenusEnabled(BOOL canNegate, BOOL canNormal, BOOL canResetOnly,
    BOOL canSetOnly, BOOL canDelete, BOOL canInsertEnd, BOOL canInsertOther,
    BOOL canPushRungDown, BOOL canPushRungUp, BOOL canInsertComment);

void SetUndoEnabled(BOOL undoEnabled, BOOL redoEnabled);
void RefreshScrollbars(void);
/*extern HINSTANCE        Instance;
extern QApplication*    LDmicroApp;
extern HWID             MainWindow;
extern QIcon*           MWIcon;*/
extern PlcProgram       Prog;
extern char             CurrentSaveFile[MAX_PATH];
extern char             CurrentCompileFile[MAX_PATH];
extern McuIoInfo        SupportedMcus[NUM_SUPPORTED_MCUS];

extern std::unique_ptr<WtMenuBar>  MenuBar;
extern std::unique_ptr<Wt::WVBoxLayout> PackBoxMenu;

extern int ColsAvailable;

class WtMain : public Wt::WApplication
{
public:
	WtMain(const Wt::WEnvironment& env);
	void MakeMainWindowControls();
    void MakeMainWindowMenus();
private:
};

/*class TopMenu : public Wt::WPopupMenu
{
public:
};*/

extern BOOL InSimulationMode;

// lang.cpp
char *_(char *in);

// memory debugging, because I often get careless; ok() will check that the
// heap used for all the program storage is not yet corrupt, and oops() if
// it is
void CheckHeap(char *file, int line);
#define ok() CheckHeap(__FILE__, __LINE__)

#endif
