import ctypes as ct
from ctypes import *
from enum import Enum

import numpy as np
import string
import random

ERROR_STRING_LEN = 1500
BUFF_STRING_LEN = 128
PRG_NAME_LEN = 300
FILE_NAME_LEN = 127
VAR_STRING_LEN = 127
VAR_NAME_LEN = 255
KERNELV_ERR_MSG_STRING_LENGTH = 23
KERNELV_ERROR_VALUE_COUNT = 5
KERNELV_CHANNEL_TECHNO_DATA_COUNT = 30
KERNELV_AXIS_TECHNO_DATA_COUNT = 30


class KERNELV_RETURN(Enum):
    RET_FINISHED = 0    # Function finished without errors. */
    RET_BUSY = 1    # Function is busy (executing but not yet finshed. */
    #
    ERR_INVALID_CHAN = -1    # Invalid channel number   */
    ERR_PROG_NAME_LENGTH = -2    # Programm name is to long.*/
    ERR_CNC_NOT_INIT = -3    # CNC not initialized      */
    # The memory passed by the caller is not big enough for alll return values.  */
    ERR_CNC_RET_MEMORY = -4
    # The channel or the axis is in the wrong mode to execute the command. */
    ERR_INVALID_STATE = -5
    ERR_DOUBLE_KERNEL = -6    # Kernel is already started. */
    ERR_SHM_STARTUP = -7    # Shared memories could not be allocated. */
    ERR_STARTUP = -8    # Error at startup of CNC kernel. */
    ERR_INVALID_AX = -9    # Error invalid axis number.      */
    ERR_AXIS_ERROR = -10    # The axis is in error state */
    ERR_INTERNAL_ERROR = -11    # Internal error */
    ERR_UNKNOWN_VARIABLE = -12    # Variable existiert nicht. */
    # Syntax error in variable name, e. g. missing closing brace. */
    ERR_VARIABLE_SYNTAX = -13
    # Data type of passed write variable is not equal to the configured type. */
    ERR_DATA_TYPE_MISMATCH = -14
    ERR_UNKNOWN_TECHNO_TYPE = -15    # Type of techno function unknown. */
    ERR_INVALID_TECHNO_PARAM = -16    # Parameter passed to function is invalid. */
    ERR_NO_LICENSE = -17    # kernelv-DLL is not licensed. */
    ERR_VAR_NAME_LENGTH = -18    # Variable name passed to function is to long. */
    ERR_REGISTRY_ACCESS = -19    # Error during access to the registry. */
    ERR_UNKNOWN_OPTION = -20    # kernelv_set_options got an unknown options flag. */
    ERR_ARRAY_NOT_SUPPORTED = -21    # Reading of array as a piece not supported. */
    ERR_VAR_NOT_WRITEABLE = -22    # The kernel variable can not be written. */
    ERR_PREFIX_TOO_LONG = -23    # Prefix is to long */
    # There is already one instance of kernelv running, startted from this DLL. */
    ERR_DOUBLE_INSTANCE = -24
    # Invalid startup mode in call of kernelv_ch_program_start() */
    ERR_INVALID_START_MODE = -25
    ERR_READ_ERR = -26    # Error while reading data from kernelv. */
    ERR_WRITE_ERR = -27    # Error while writing data to kernelv. */
    ERR_CNC_NO_DATA = -28    # Error the request data is not available. */
    ERR_TECHNO_NOT_FOUND = -29    # Error the techno function was not found. */
    ERR_INVALID_PARAMETER = -30    # Calling parameters are invalid. */


class CHANNEL_STATE(Enum):
    DESELECTED = 1
    SELECTED = 2
    READY = 3
    ACTIVE = 4
    HOLD = 5
    ERROR = 6

    SELECTING = 7
    DESELECTING = 8
    PREPARING = 9
    CLEARING = 10
    STARTING = 11
    ABORTING = 12
    STOPPING = 13
    RESUMING = 14
    RESETTING = 15
    FINISHING = 16


"""
CHANNEL_STATE = {
  'DESELECTED':   1 ,
  'SELECTED':   2 ,
  'READY':   3 ,
  'ACTIVE':   4 ,
  'HOLD':   5 ,
  'ERROR':   6 ,

  'SELECTING':   7 ,
  'DESELECTING':   8 ,
  'PREPARING':   9 ,
  'CLEARING':   10,
  'STARTING':   11,
  'ABORTING':   12,
  'STOPPING':   13,
  'RESUMING':   14,
  'RESETTING':   15,
  'FINISHING':   16
}
"""

####################################################################################################
###                    TECHNO_DATA STRUCTS                                                       ###
####################################################################################################


class SPINDEL_TYPE(Enum):
    UNKNOWN = 0
    M3 = 1         # Spindle code M3.
    M4 = 2         # Spindle code M4.
    M5 = 3         # Spindle code M5.
    M19 = 4         # Spindle code M19.


class TECHNO_TYPE(Enum):
    EMPTY = 0         # Entry is not used
    M_CODE = 1         # M code
    H_CODE = 2         # H code
    S_CODE = 3         # S code
    T_CODE = 4         # T code


class M_H_CODE_DATA(Structure):
    _fields_ = [('nr', ct.c_ulong),
                ('duration', ct.c_ulong)]


class S_CODE_DATA(Structure):
    _fields_ = [('SPINDLE_TYPE', ct.c_int),
                ('axis_number', ct.c_ushort),
                ('revolutions', ct.c_ulong),
                ('position', ct.c_long),
                ('duration', ct.c_ulong)]


class T_CODE_DATA(Structure):
    _fields_ = [('basic', ct.c_long),
                ('sister', ct.c_long),
                ('variant', ct.c_long)]


class TECHNO_PARAM(Union):
    _pack_ = True
    _fields_ = [('M_H_CODE_DATA', M_H_CODE_DATA),
                ('S_CODE_DATA', S_CODE_DATA),
                ('T_CODE_DATA', T_CODE_DATA)]


class TECHNO_DATA(Structure):
    _fields_ = [('TECHNO_TYPE', ct.c_int),
                ('TECHNO_PARAM', TECHNO_PARAM)]


####################################################################################################
###                    TECHNO_DATA2 STRUCTS                                                      ###
####################################################################################################

class M_H_CODE_DATA2(Structure):
    _fields_ = [('nr', ct.c_ulong),
                ('duration', ct.c_ulong),
                ('add_value', ct.c_long),
                ('fillup', ct.c_ulong)]


class TECHNO_PARAM2(Union):
    _pack_ = True
    _fields_ = [('M_H_CODE_DATA', M_H_CODE_DATA2),
                ('S_CODE_DATA', S_CODE_DATA),
                ('T_CODE_DATA', T_CODE_DATA)]


class TECHNO_DATA2(Structure):
    _fields_ = [('TECHNO_TYPE', ct.c_int),
                ('TECHNO_PARAM2', TECHNO_PARAM2)]


####################################################################################################
###                    NC_LINE_DATA STRUCTS                                                      ###
####################################################################################################

class NC_LINE_DATA(Structure):
    _fields_ = [('fileoffset', ct.c_ulong),
                ('ncLineNumber', ct.c_ulong),
                ('filename', ct.c_char*84)]


####################################################################################################
###                    VARIABLE STRUCTS                                                      ###
####################################################################################################

class VAR_VALUE(Union):
    _pack_ = True
    _fields_ = [('uns08', ct.c_char),
                ('sgn08', ct.c_char),
                ('uns16', ct.c_ushort),
                ('sgn16', ct.c_short),
                ('uns32', ct.c_ulong),
                ('sgn32', ct.c_long),
                ('real64', ct.c_double),
                ('boolean', ct.c_char),
                ('string', ct.c_char*128)]


class VAR_TYPE (Enum):
    UNKNOWN = 1
    BOOLEAN = 2  # Variable is a BOOLEAN
    UNS08 = 3  # Variable is a unsigned 8 bit integer
    SGN08 = 4  # Variable is a signed 8 bit integer
    UNS16 = 5  # Variable is a unsigned 16 bit integer
    SGN16 = 6  # Variable is a signed 16 bit integer
    UNS32 = 7  # Variable is a unsigned 32 bit integer
    SGN32 = 8  # Variable is a signed 32 bit integer
    DOUBLE = 9  # Variable is a 64 bit floating point number
    STRING = 10  # Variable is a string


class VARIABLE(Structure):
    _fields_ = [('VAR_TYPE', ct.c_int),
                ('VAR_VALUE', VAR_VALUE)]


####################################################################################################
###                    LICENSE STRUCT                                                            ###
####################################################################################################


# -------------------------------------------------------------
class LICENSE_INFO(Structure):
    _fields_ = [('CncSysIdOK', ct.c_long),                      # License check successfull.
                # Number of licensed axes.
                ('CncAxesPack', ct.c_long),
                # Number of licensed channels
                ('CncChannels', ct.c_long),
                # Transformation package licensed
                ('CncTrafo', ct.c_long),
                # Spline package licensed.
                ('CncSpline', ct.c_long),
                ('CncExport', ct.c_long),                       # Export license
                ('CncDll', ct.c_long),]                         # kernelv is licensed.
    # -------------------------------------------------------------


##############################################################################################################################


class PROG_START_MODE (Enum):  # -----------------------------
    UKNOWN = -1
    NORMAL = 0         # Normale Bearbeitung.
    CONTOUR_VISU = 1         # Contuour visualisation.
    # ------------------------------


####################################################################################################
###                    G_GROUP ENUM and STRUCT                                                   ###
####################################################################################################

class G_GROUP_TYPE(Enum):
    # (G00,G01,G02,G03,G04,G33,G63,G74,G98,G99,G301,G302,G160) AEP_WEG_BED
    G_PATH_COND = 0
    G_PATH_FEED = 1  # (G08,G193) AEP_VB_VORSCH
    G_DEC = 2  # (G09,G900,G901) AEP_GESCHW
    G_FEED_ADAPT = 3  # (G09,G900,G901) AEP_WRK_VB
    G_ACITVE_PLANE = 4  # (G17,G18,G19) AEP_EBENE
    G_MIRROR = 5  # (G20,G21,G22,G23,G24,G351) AEP_SPIEGEL
    G_TRC_TRANSITION = 6  # (G25,G26) AEP_WRK_UEBER
    G_TOOL_RADIUS_COMP = 7  # (G40,G41,G42) AEP_WZ_KORR
    G_DIAMETER_PROG = 8  # (G40,G41,G42) AEP_DURCHM
    G_ZERO_POS_SHIFT = 9  # (G53-G59,G159) AEP_NULLP
    G_EXACT_STOP = 10  # (G60,G359,G360,G260,G261) AEP_GENAUHALT
    G_OVERRRIDE_100 = 11  # (G166) AEP_OVERRIDE
    G_UNIT = 12  # AEP_MASSEINH (G70,G71)
    G_SUB_CALL = 13  # (G80-G89,G800-G819) AEP_ARB_ZYK
    G_ABS_REL = 14  # (G90,G91) AEP_MASSANG
    G_POS_SHIFT = 15  # (G92) AEP_BZP
    G_FEED_PROG = 16                     # G93,G94,G95,G194) AEP_F_VRG
    G_SPINDEL_FEED = 17  # (G96,G97,G196)   AEP_S_VRG
    G_GEAR_CHANGE = 18  # (G112) AEP_GETRIEBE
    G_LOOKAHEAD = 19  # (G115,G116,G117) AEP_BAVO
    G_ACC_WEIGHT = 20  # (G130,G131) AEP_BESCHL
    G_FEEDFORWARD = 21  # (G135,G136,G137) AEP_VORST
    G_TRC_SELCECTION = 22  # (G05,G138,G139,G237,G238,G239) AEP_WRK_E_A
    G_CIRCE_CENTER = 23  # (G161,G162) AEP_MPKT_A_R
    G_RADIUS_PROGR = 24  # (G163) AEP_RADIUS
    G_CIRC_CENTER_CORR = 25  # (G164,G165) AEP_MPKT_KORR
    G_MANUAL_MODE = 26  # (G200,G201,G202) AEP_HAND
    G_RAMP_TIME_WEIGHT = 27  # G132,G133,G134) AEP_RAMPE_ZT
    G_SPLINE = 28  # (G150,G151) AEP_ASPLINE
    G_PROBING = 29  # (G100,G101,G102,G106,G107,G108) AEP_MESSEN
    G_CORNER_DECEL = 30  # (G12,G13) AEP_CORNER
    G_CONTOUR_MASKING = 31  # (G140,G141) AEP_CONT_MASK
    G_PROBING_INTERR = 32  # (G310) AEP_INTER
    G_SPINDLE_OVERRRIDE = 33  # (G167) AEP_SPDL_OVERRIDE
    G_RAPID_FEED_WEIGHT = 34  # (G129) AEP_FEED_WEIGHTING
    G_MAX_G_GRP = 35  # Number of groups, size of array


class ACTIVE_G_CODES(Structure):
    _fields_ = [('G_MAX_G_GRP', ct.c_short*G_GROUP_TYPE.G_MAX_G_GRP.value)]

####################################################################################################
###                    ERROR VALUE DATA STRUCTS                                                  ###
####################################################################################################


class ERR_VAL_TYPE(Enum):
    ERR_VAL_TYPE_UNKNOWN = - 1  # unbekannter Datentyp, evtl. generisch, Token vom Typ NONE
    ERR_VAL_TYPE_BOOLEAN = 0  # Typ einer BOOLEAN-Variable und eines Tokens vom Typ BOOLEAN
    ERR_VAL_TYPE_UNS08 = 1  # Typ einer UNS08  -Variable und eines Tokens vom Typ UNS08
    ERR_VAL_TYPE_SGN08 = 2  # Typ einer SGN08  -Variable und eines Tokens vom Typ SGN08
    ERR_VAL_TYPE_UNS16 = 3  # Typ einer UNS16  -Variable und eines Tokens vom Typ UNS16
    ERR_VAL_TYPE_SGN16 = 4  # Typ einer SGN16  -Variable und eines Tokens vom Typ SGN16
    ERR_VAL_TYPE_UNS32 = 5  # Typ einer UNS32  -Variable und eines Tokens vom Typ UNS32
    ERR_VAL_TYPE_SGN32 = 6  # Typ einer SGN32  -Variable und eines Tokens vom Typ SGN32
    ERR_VAL_TYPE_UNS64 = 7  # Typ einer UNS64  -Variable und eines Tokens vom Typ UNS64
    ERR_VAL_TYPE_SGN64 = 8  # Typ einer SGN64  -Variable und eines Tokens vom Typ SGN64
    ERR_VAL_TYPE_REAL64 = 9  # Typ einer REAL64 -Variable und eines Tokens vom Typ REAL64
    ERR_VAL_TYPE_REAL32 = 10  # Tokentyp REAL32
    ERR_VAL_TYPE_CHAR = 11  # Tokentyp CHAR
    ERR_VAL_TYPE_STRING = 12  # Tokentyp STRING
    ERR_VAL_TYPE_ADRESSE = 13  # Tokentyp ADRESSE
    ERR_VAL_TYPE_IGNORE = 14  # Tokentyp Ignorieren des Tokens (šberlesen)
    ERR_VAL_TYPE_A3_REAL64 = 15  # Tokentyp REAL64[3]
    ERR_VAL_TYPE_BITARRAY_32 = 16  # Tokentyp Bitarray 32
    ERR_VAL_TYPE_BITARRAY_16 = 17  # Tokentyp Bitarray 16


class ERR_VAL_DIMENSION(Enum):
    ERR_VAL_DIM_UNKNOWN = - 1  # keine Dimensionsangabe
    ERR_VAL_DIM_NO_DIM = 0  # dimensionslos      in [-]
    ERR_VAL_DIM_POSITION = 1  # Position           in [0.1 10^-3 mm bzw. ø]
    ERR_VAL_DIM_POSITION_HIGH_RES = 2  # Position           in [10^7 mm bzw. ø]
    ERR_VAL_DIM_VELOCITY = 3  # Geschwindigkeit    in [10^-3 mm/s bzw. ø/s]
    ERR_VAL_DIM_ACCELERATION = 4  # Beschleunigung     in [mm/s^2 bzw. ø/s^2]
    ERR_VAL_DIM_JERK = 5  # Ruck               in [mm/s^3 bzw. ø/s^3]
    ERR_VAL_DIM_TIME = 6  # Zeit               in [us]
    ERR_VAL_DIM_PERMILL = 7  # Prozent            in [0.1 %]
    ERR_VAL_DIM_INKREMENTS = 8  # Weginkremente      in [-]
    ERR_VAL_DIM_REV_FEED = 9  # Umdrehungsvorschub in [0.1 10^-3 mm/U]
    ERR_VAL_DIM_CUTTING_SPEED = 10  # Schnittgeschw.     in [10^-3 mm/s]
    # Wegauflosung       in [Inkremente / 0.1 um ]
    ERR_VAL_DIM_PATH_RESOLUTION = 11
    # Inkremente pro Umdrehung [Inkremente / Umdrehung ]
    ERR_VAL_DIM_INCR_PER_REV = 12
    ERR_VAL_DIM_BYTE = 13  # Byte               in [-]
    ERR_VAL_DIM_PROPORTIONAL_GAIN = 14  # Proportionalverstaerkung in [0.01 /s]
    ERR_VAL_DIM_FREQUENCY = 15  # Frequenz           in [Hz]
    ERR_VAL_DIM_LOAD = 16  # Motorlast          in kg bzw. kg*m**2


class ERR_VAL_MEANING(Enum):
    ERR_VAL_MEAN_UNKNOWN = - 1
    ERR_VAL_MEAN_LIMIT = 0  # Grenzwert
    ERR_VAL_MEAN_ACT_VAL = 1  # aktueller Wert
    ERR_VAL_MEAN_ERR_VAL = 2  # fehlerhafter Wert
    ERR_VAL_MEAN_EXPECT_VAL = 3  # erwarteter Wert
    ERR_VAL_MEAN_CORR_VAL = 4  # korrigierter Wert
    ERR_VAL_MEAN_LOG_AXIS_NR = 5  # logische Achsnummer
    ERR_VAL_MEAN_DRIVE_TYPE = 6  # Antriebstyp
    ERR_VAL_MEAN_LOG_BED_ELEM_NR = 7  # logische Beienelementnummer
    ERR_VAL_MEAN_STATE = 8  # Zustand
    ERR_VAL_MEAN_TRANSITION = 9  # Transition
    ERR_VAL_MEAN_SENDER = 10  # Sender
    ERR_VAL_MEAN_CLASS = 11  # Klasse
    ERR_VAL_MEAN_INSTANCE = 12  # Instanz
    ERR_VAL_MEAN_IDENT_NR = 13  # Identifikationsnummer
    ERR_VAL_MEAN_STATUS = 14  # Status
    ERR_VAL_MEAN_RING_NR = 15  # Ringnummer
    ERR_VAL_MEAN_SATZ_NR = 16  # Satznummer
    ERR_VAL_MEAN_MIN_LIMIT = 17  # unterer Grenzwert
    ERR_VAL_MEAN_MAX_LIMIT = 18  # oberer Grenzwert
    ERR_VAL_MEAN_START_VAL = 19  # Startwert
    ERR_VAL_MEAN_TARGET_VAL = 20  # Endwert
    ERR_VAL_MEAN_FILENAME = 21  # Dateiname
    ERR_VAL_MEAN_LINE = 22  # Zeile (Text) in einer Datei
    ERR_VAL_MEAN_LINE_NUMBER = 23  # Zeilennummer in einer Datei
    ERR_VAL_MEAN_COLUMN_NUMBER = 24  # Spaltennummer in einer Datei
    ERR_VAL_MEAN_ARGUMENT = 25  # Argument
    ERR_VAL_MEAN_PARAMETER = 26  # Parameter
    ERR_VAL_MEAN_AXIS = 27  # Axis (String)
    ERR_VAL_MEAN_COMPENSATION = 28  # Compensation index
    ERR_VAL_MEAN_IDENTIFIER = 29  # Identifier
    ERR_VAL_MEAN_CHAIN = 30  # Chain


class ERR_VAL_DATA(Union):
    _pack_ = True
    _fields_ = [('adresse',    ct.c_void_p),  # Zeiger auf eine Adresse
                ('boolean',    ct.c_char),  # Boolescher Wert (TRUE/FALSE)
                ('uns08',      ct.c_char),  # Vorzeichenloser 8-Bit Ganzzahlwert
                # Vorzeichenbehafteter 8-Bit Ganzzahlwert
                ('sgn08',      ct.c_char),
                ('isg_char',   ct.c_char),  # Zeichenkonstante
                # Vorzeichenloser 16-Bit Ganzzahlwert
                ('uns16',      ct.c_ushort),
                # Vorzeichenbehafteter 16-Bit Ganzzahlwert
                ('sgn16',      ct.c_short),
                # Vorzeichenloser 32-Bit Ganzzahlwert
                ('uns32',      ct.c_ulong),
                # Vorzeichenbehafteter 32-Bit Ganzzahlwert
                ('sgn32',      ct.c_long),
                ('real64',     ct.c_double),  # Reeller Wert
                # Vorzeichenbehafteter 64-Bit Ganzzahlwert.
                ('sgn64',      ct.c_ulonglong),
                # Vorzeichenloser 64-Bit Ganzzahlwert.
                ('uns64',      ct.c_longlong),
                # Zeichenkette
                ('string',     ct.c_char*(KERNELV_ERR_MSG_STRING_LENGTH + 1)),
                ('a3_real64',  (ct.c_double*3))]  # Array aus 3 Realwerten fuer Punktausgabe


class ERROR_VALUE(Structure):
    _pack_ = True
    _fields_ = [('type',        ct.c_int),                              # Data type of error value
                # Dimension of error value
                ('dimension',   ct.c_int),
                # Meaning of error value
                ('meaning',     ct.c_int),
                ('fillup',      ct.c_long),
                ('data',        ERR_VAL_DATA)]                          # Data content of error value


####################################################################################################
###                    DECODER STRUCTS                                                           ###
####################################################################################################

class DECODER_POSITION_HEADER(Structure):
    _pack_ = True  # -----------------------------------------------------------------------------
    _fields_ = [('data_valid',    ct.c_bool),                          # Indication that the steam contains valid data
                # last prgrammed block number (N-number) in NC programm
                ('line_number',   ct.c_long),
                # Counter for decoded NC_lines
                ('block_count',   ct.c_long),
                ('axis_count',    ct.c_short)]                         # Number of axes (number of data records)
    # -----------------------------------------------------------------------------


class DECODER_POSITION_DATA(Structure):
    _pack_ = True  # -----------------------------------------------------------------------------
    _fields_ = [('mcs_pos',             ct.c_long),                    # Axis position in MCS (machine coordinate system).
                # Axis position in PCS (programming coordinate system) without offsets (PCS1)
                ('pcs_pos_no_offset',   ct.c_long),
                # Axis position in PCS (programming coordinate system) including offsets(PCS2)
                ('pcs_pos_offset',      ct.c_long),
                ('axis_number',         ct.c_short)]                   # Axis number
    # -----------------------------------------------------------------------------


class DECODER_POSITIONS(Structure):
    _pack_ = True  # -----------------------------------------------------------------------------
    _fields_ = [('HEADER',             DECODER_POSITION_HEADER),
                ('DATA',               DECODER_POSITION_DATA*32)]


####################################################################################################
###                    FUNCTIONS                                                                 ###
####################################################################################################

def load(sDllpath):
    vNCK = ct.cdll.LoadLibrary(sDllpath)
    return vNCK


def startup(vNCK, iCyleTime, sStartupfile, kernelKey):
    startup_lis = ct.c_char_p(sStartupfile)
    # instanceKey = ''.join(random.choices(
    # string.ascii_uppercase + string.digits, k=10))
    print("Kernel Key ist ", kernelKey)
    instancePrefix = ct.c_char_p(kernelKey.encode())

    ret = vNCK.kernelv_startup_instance(iCyleTime, startup_lis, instancePrefix)
    return ret


def get_error(vNCK):
    err_id = ct.c_ulong()
    err_str = ct.create_string_buffer(ERROR_STRING_LEN)
    err_str_length = ct.c_ulong()

    ret = vNCK.kernelv_get_error(
        ct.byref(err_id), err_str, ERROR_STRING_LEN, ct.byref(err_str_length))
    iErrorID = err_id.value
    sErrString = err_str.value
    return ret, iErrorID, sErrString


def get_api_version(vNCK):
    api_ver_str = ct.create_string_buffer(BUFF_STRING_LEN)
    api_ver_size = ct.c_ulong()

    ret = vNCK.kernelv_get_api_version(
        ct.byref(api_ver_str), BUFF_STRING_LEN, ct.byref(api_ver_size))
    api_version = api_ver_str.value
    return ret, api_version


def get_cnc_version(vNCK):
    cnc_ver_str = ct.create_string_buffer(BUFF_STRING_LEN)
    cnc_ver_size = ct.c_ulong()

    ret = vNCK.kernelv_get_cnc_version(
        ct.byref(cnc_ver_str), BUFF_STRING_LEN, ct.byref(cnc_ver_size))
    cnc_version = cnc_ver_str.value
    return ret, cnc_version


def get_cycletime(vNCK):
    cycletime = ct.c_ulong()

    ret = vNCK.kernelv_get_cycletime(ct.byref(cycletime))
    cycletime = cycletime.value
    return ret, cycletime


def startup_instance(vNCK, cycletime, sStartupfile, instance_prefix):
    startup_lis = ct.c_char_p(sStartupfile)
    instance_pre = ct.c_char_p(instance_prefix)

    ret = vNCK.kernelv_startup_instance(cycletime, startup_lis, instance_pre)
    return ret


def do_cycle(vNCK):
    ret = vNCK.kernelv_do_cycle()
    return ret


def ch_program_start(vNCK, chan_index, programm_name, edit_mode):
    index = ct.c_long(chan_index)
    name = ct.c_char_p(programm_name)
    mode = ct.c_long(edit_mode)

    ret = vNCK.kernelv_ch_program_start(index, name, mode)
    return ret


def ch_reset(vNCK, chan_index):
    index = ct.c_long(chan_index)

    ret = vNCK.kernelv_ch_reset(index)
    return ret


def ch_suspend(vNCK, chan_index):
    index = ct.c_long(chan_index)

    ret = vNCK.kernelv_ch_suspend(index)
    return ret


def ch_resume(vNCK, chan_index):
    index = ct.c_long(chan_index)

    ret = vNCK.kernelv_ch_resume(index)
    return ret


def ch_set_override(vNCK, chan_index):
    index = ct.c_long(chan_index)
    override = ct.c_short()

    ret = vNCK.kernelv_ch_get_override(index, ct.byref(override))
    return ret


def ch_get_blocknumber(vNCK, chan_index):
    index = ct.c_long(chan_index)
    blocknumber = ct.c_long()

    ret = vNCK.kernelv_ch_get_blocknumber(index, ct.byref(blocknumber))
    return ret, blocknumber.value


def ch_get_filename(vNCK, chan_index):
    index = ct.c_long(chan_index)
    filename = ct.create_string_buffer(FILE_NAME_LEN)
    returnLength = ct.c_ushort()

    ret = vNCK.kernelv_ch_get_filename(index, ct.byref(
        filename), FILE_NAME_LEN, ct.byref(returnLength))
    return ret, filename.value


def ch_get_programname(vNCK, chan_index):
    index = ct.c_long(chan_index)
    programname = ct.create_string_buffer(PRG_NAME_LEN)
    returnLength = ct.c_ushort()

    ret = vNCK.kernelv_ch_get_programname(index, ct.byref(
        programname), PRG_NAME_LEN, ct.byref(returnLength))
    return ret, programname.value


def ch_get_state(vNCK, chan_index):
    index = ct.c_long(chan_index)
    state = ct.c_int()

    ret = vNCK.kernelv_ch_get_state(index, ct.byref(state))
    return ret, state


def ch_get_fileoffset(vNCK, chan_index):
    index = ct.c_long(chan_index)
    fileoffset = ct.c_long()

    ret = vNCK.kernelv_ch_get_fileoffset(index, ct.byref(fileoffset))
    return ret, fileoffset.value


def ch_get_techno_data(vNCK, chan_index):
    index = ct.c_long(chan_index)
    techno_data = (TECHNO_DATA*KERNELV_CHANNEL_TECHNO_DATA_COUNT)()
    returnLength = ct.c_ulong()

    ret = vNCK.kernelv_ch_get_techno_data(
        index, ct.pointer(techno_data), 1000, ct.byref(returnLength))
    # for i in range(KERNELV_CHANNEL_TECHNO_DATA_COUNT):
    #    print('TECHNODATA[{}] type:{}, \n M_H_CODE_DATA_nr:{},M_H_CODE_DATA_duration:{}, \n S_CODE_DATA_SPINDLE_TYPE:{}, S_CODE_DATA_axis_number:{}, S_CODE_DATA_revolutions:{} \n, S_CODE_DATA_position:{}, S_CODE_DATA_duration:{}, \n \
    #    T_CODE_DATA_basic:{}, T_CODE_DATA_sister:{}, T_CODE_DATA_variant:{} \n'.format(i, techno_data[i].TECHNO_TYPE, techno_data[i].TECHNO_PARAM.M_H_CODE_DATA.nr, techno_data[i].TECHNO_PARAM.M_H_CODE_DATA.duration, techno_data[i].TECHNO_PARAM.S_CODE_DATA.SPINDLE_TYPE, \
    #        techno_data[i].TECHNO_PARAM.S_CODE_DATA.axis_number, techno_data[i].TECHNO_PARAM.S_CODE_DATA.revolutions, techno_data[i].TECHNO_PARAM.S_CODE_DATA.position, techno_data[i].TECHNO_PARAM.S_CODE_DATA.duration, \
    #       techno_data[i].TECHNO_PARAM.T_CODE_DATA.basic, techno_data[i].TECHNO_PARAM.T_CODE_DATA.sister, techno_data[i].TECHNO_PARAM.T_CODE_DATA.variant ))
    return ret, techno_data, returnLength.value


def ch_get_new_techno_data(vNCK, chan_index):
    index = ct.c_long(chan_index)
    techno_data = (TECHNO_DATA*KERNELV_CHANNEL_TECHNO_DATA_COUNT)()
    returnLength = ct.c_ulong()

    ret = vNCK.kernelv_ch_get_new_techno_data(
        index, ct.pointer(techno_data), 1000, ct.byref(returnLength))
    return ret, techno_data


def ch_get_techno_data2(vNCK, chan_index):
    index = ct.c_long(chan_index)
    techno_data2 = (TECHNO_DATA2*KERNELV_CHANNEL_TECHNO_DATA_COUNT)()
    returnLength = ct.c_ulong()

    ret = vNCK.kernelv_ch_get_techno_data2(
        index, ct.pointer(techno_data2), 1000, ct.byref(returnLength))
    return ret, techno_data2


def ch_get_new_techno_data2(vNCK, chan_index):
    index = ct.c_long(chan_index)
    techno_data2 = (TECHNO_DATA2*KERNELV_CHANNEL_TECHNO_DATA_COUNT)()
    returnLength = ct.c_ulong()

    ret = vNCK.kernelv_ch_get_new_techno_data2(
        index, ct.pointer(techno_data2), 1000, ct.byref(returnLength))
    return ret, techno_data2


def ch_get_finished_nc_lines(vNCK, chan_index):
    index = ct.c_long(chan_index)
    ncLineData = NC_LINE_DATA()
    returnLength = ct.c_ulong()

    ret = vNCK.kernelv_ch_get_finished_nc_lines(
        index, ct.pointer(ncLineData), 4000, ct.byref(returnLength))
    return ret, ncLineData.fileoffset, ncLineData.ncLineNumber, ncLineData.filename


def ax_get_techno_data(vNCK, axis_index):
    index = ct.c_long(axis_index)
    techno_data = (TECHNO_DATA*KERNELV_CHANNEL_TECHNO_DATA_COUNT)()
    returnLength = ct.c_ulong()

    ret = vNCK.kernelv_ax_get_techno_data(
        index, ct.pointer(techno_data), 1000, ct.byref(returnLength))
    return ret, techno_data


def ax_get_new_techno_data(vNCK, axis_index):
    index = ct.c_long(axis_index)
    techno_data = (TECHNO_DATA*KERNELV_CHANNEL_TECHNO_DATA_COUNT)()
    returnLength = ct.c_ulong()

    ret = vNCK.kernelv_ax_get_new_techno_data(
        index, ct.pointer(techno_data), 1000, ct.byref(returnLength))
    return ret, techno_data


def ax_get_techno_data2(vNCK, axis_index):
    index = ct.c_long(axis_index)
    techno_data2 = (TECHNO_DATA2*KERNELV_CHANNEL_TECHNO_DATA_COUNT)()
    returnLength = ct.c_ulong()

    ret = vNCK.kernelv_ax_get_techno_data2(
        index, ct.pointer(techno_data2), 1000, ct.byref(returnLength))
    return ret, techno_data2


def ax_get_new_techno_data2(vNCK, axis_index):
    index = ct.c_long(axis_index)
    techno_data2 = (TECHNO_DATA2*KERNELV_CHANNEL_TECHNO_DATA_COUNT)()
    returnLength = ct.c_ulong()

    ret = vNCK.kernelv_ax_get_new_techno_data2(
        index, ct.pointer(techno_data2), 1000, ct.byref(returnLength))
    return ret, techno_data2


def ax_set_position(vNCK, axis_index, soll_position):
    index = ct.c_ulong(axis_index)
    position = ct.c_ulong(soll_position)

    ret = vNCK.kernelv_ax_set_position(index, position)
    return ret


def get_acs_command_positions(vNCK):
    positions = (ct.c_long*35)()
    retSize = ct.c_ulong()

    ret = vNCK.kernelv_get_acs_command_positions(
        ct.pointer(positions), 70, ct.byref(retSize))
    positionvalues = positions
    return ret, np.array(list(positionvalues)), retSize.value


def get_acs0_command_positions(vNCK):
    positions = (ct.c_long*35)()
    retSize = ct.c_ulong()

    ret = vNCK.kernelv_get_acs0_command_positions(
        ct.pointer(positions), 70, ct.byref(retSize))
    positionvalues = positions
    return ret, np.array(list(positionvalues)), retSize.value


def get_acs_actual_positions(vNCK):
    positions = (ct.c_long*35)()
    retSize = ct.c_ulong()

    ret = vNCK.kernelv_get_acs_actual_positions(
        ct.pointer(positions), 70, ct.byref(retSize))
    positionvalues = positions
    return ret, np.asarray(list(positionvalues)), retSize.value


def get_acs_target_positions(vNCK):
    positions = (ct.c_long*35)()
    retSize = ct.c_ulong()

    ret = vNCK.kernelv_get_acs_target_positions(
        ct.pointer(positions), 1000, ct.byref(retSize))
    positionvalues = positions
    return ret, np.array(list(positionvalues)), retSize.value


def get_acs_start_positions(vNCK):
    positions = (ct.c_long*35)()
    retSize = ct.c_ulong()

    ret = vNCK.kernelv_get_acs_start_positions(
        ct.pointer(positions), 1000, ct.byref(retSize))
    positionvalues = positions
    return ret, np.array(list(positionvalues)), retSize.value


def get_wcs_command_positions(vNCK):
    positions = (ct.c_long*35)()
    retSize = ct.c_ulong()

    ret = vNCK.kernelv_get_wcs_command_positions(
        ct.pointer(positions), 1000, ct.byref(retSize))
    positionvalues = positions
    return ret, np.array(list(positionvalues)), retSize.value


def get_wcs_target_positions(vNCK):
    positions = (ct.c_long*35)()
    retSize = ct.c_ulong()

    ret = vNCK.kernelv_get_wcs_target_positions(
        ct.pointer(positions), 1000, ct.byref(retSize))
    positionvalues = positions
    return ret, np.array(list(positionvalues)), retSize.value


def get_wcs_start_positions(vNCK):
    positions = (ct.c_long*35)()
    retSize = ct.c_ulong()

    ret = vNCK.kernelv_get_wcs_start_positions(
        ct.pointer(positions), 1000, ct.byref(retSize))
    positionvalues = positions
    return ret, np.array(list(positionvalues)), retSize.value


def get_prg_target_positions(vNCK):
    positions = (ct.c_long*35)()
    retSize = ct.c_ulong()

    ret = vNCK.kernelv_get_prg_target_positions(
        ct.pointer(positions), 1000, ct.byref(retSize))
    positionvalues = positions
    return ret, np.array(list(positionvalues)), retSize.value


def get_axis_channel_number(vNCK):
    chanNumbers = (ct.c_short*30)()
    retSize = ct.c_ulong()

    ret = vNCK.kernelv_get_axis_channel_number(
        ct.pointer(chanNumbers), 1000, ct.byref(retSize))
    return ret, list(chanNumbers), retSize.value


def ch_get_variable_value(vNCK, chan_index, variable_name):
    index = ct.c_long(chan_index)
    var_Name = variable_name.encode('utf-8')
    varName = ct.create_string_buffer(var_Name)
    var = VARIABLE()

    ret = vNCK.kernelv_ch_get_variable_value(index, varName, ct.pointer(var))
    return ret, var


def ch_set_variable_value(vNCK, chan_index, variable_name, variable):
    index = ct.c_long(chan_index)
    var_Name = variable_name.encode('utf-8')
    varName = ct.create_string_buffer(var_Name)

    ret = vNCK.kernelv_ch_set_variable_value(
        index, ct.pointer(varName), ct.pointer(variable))
    return ret, variable


def get_channel_count(vNCK):
    channelCount = ct.c_ulong()

    ret = vNCK.kernelv_get_channel_count(byref(channelCount))
    return ret, channelCount


def get_axis_count(vNCK):
    axisCount = ct.c_ulong()

    ret = vNCK.kernelv_get_axis_count(byref(axisCount))
    return ret, axisCount


def sync_read_req(vNCK, port_number, group, offset):
    port = ct.c_ushort(port_number)
    indexGroup = ct.c_ulong(group)
    indexOffset = ct.c_ulong(offset)
    length = ct.c_ulong()
    data = ct.c_double()
    pdata = ct.c_void_p()

    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_req(
        port, indexGroup, indexOffset, ct.byref(length), pdata)
    return ret, pdata


def sync_write_req(vNCK, port_number, group, offset):
    port = ct.c_ushort(port_number)
    indexGroup = ct.c_ulong(group)
    indexOffset = ct.c_ulong(offset)
    length = ct.c_ulong()
    data = ct.c_double()
    pdata = ct.c_void_p()

    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_write_req(
        port, indexGroup, indexOffset, ct.byref(length), pdata)
    return ret, pdata


def sync_read_write_req(vNCK, port_number, group, offset):
    port = ct.c_ushort(port_number)
    indexGroup = ct.c_ulong(group)
    indexOffset = ct.c_ulong(offset)
    data = ct.c_double()
    pdata = ct.c_void_p()
    readLength = ct.c_ulong()
    writeLength = ct.c_ulong(200)

    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_write_request(
        port, indexGroup, indexOffset, ct.byref(readLength), writeLength, pdata)
    return ret, pdata


def read_act_tool_length(vNCK, chan_index):
    ChNbr = chan_index + 1
    port = ct.c_ushort(552)
    indexGroup = ct.c_ulong((int("0x2230"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0x3E", 0))
    readLength = ct.c_ulong(24)
    data = ct.create_string_buffer(b"V.G.WZ_AKT.L", 24)
    pdata = ct.c_void_p
    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_write_request(
        port, indexGroup, indexOffset, ct.byref(readLength), ct.c_ulong(24), ct.byref(data))
    pdata = ct.cast(pdata, POINTER(c_int))
    return ret, pdata.contents.value  # returns tool_length in 0.1 micrometers


def read_act_tool_radius(vNCK, chan_index):
    ChNbr = chan_index + 1
    port = ct.c_ushort(552)
    indexGroup = ct.c_ulong((int("0x2230"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0x3E", 0))
    readLength = ct.c_ulong(24)
    data = ct.create_string_buffer(b"V.G.WZ_AKT.R", 24)
    pdata = ct.c_void_p
    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_write_request(
        port, indexGroup, indexOffset, ct.byref(readLength), ct.c_ulong(24), ct.byref(data))
    pdata = ct.cast(pdata, POINTER(c_int))
    return ret, pdata.contents.value  # returns tool_radius in 0.1 micrometers


def read_vg_variable(vNCK, chan_index, name, type):
    ChNbr = chan_index + 1
    port = ct.c_ushort(552)
    indexGroup = ct.c_ulong((int("0x2230"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0x3E", 0))
    readLength = ct.c_ulong(24)
    var_name = name.encode('utf-8')
    data = ct.create_string_buffer(var_name, 24)
    pdata = ct.c_void_p
    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_write_request(
        port, indexGroup, indexOffset, ct.byref(readLength), ct.c_ulong(24), ct.byref(data))

    if (type == 'SGN32'):
        pdata = ct.cast(pdata, POINTER(c_int32))
    elif (type == 'UNS32'):
        pdata = ct.cast(pdata, POINTER(c_uint32))
    elif (type == 'REAL64'):
        pdata = ct.cast(pdata, POINTER(c_double))
    else:
        ret = -2
        pdata = ct.cast(pdata, POINTER(c_int))

    return ret, pdata.contents.value


def get_axis_names(vNCK, axis_count, maxByteSize):
    axisNames = ct.create_string_buffer(maxByteSize)
    returnSize = ct.c_ulong()
    nAxis = ct.c_ulong()

    ret = vNCK.kernelv_get_axis_names(
        ct.byref(axisNames), maxByteSize, ct.byref(returnSize), ct.byref(nAxis))
    namelength = int(returnSize.value / axis_count)

    axisNameslist = []
    j = 0
    for i in range(axis_count):
        axisNameslist.append(axisNames[(j*namelength):((i+1)*namelength)])
        axisNameslist[i] = axisNameslist[i].rstrip(
            b'\x00')  # removes empty bytes
        # decodes bytes to strings, can be commented out if bytes are desired
        axisNameslist[i] = axisNameslist[i].decode('utf-8')
        j += 1
    # print('axisNameslist:',axisNameslist)
    return ret, returnSize, nAxis, axisNameslist, namelength


def control_techno_func_duration(vNCK, onoff):
    onOff = ct.c_char(onoff)

    ret = vNCK.kernelv_control_techno_func_duration(onOff)
    return ret, onOff.value


def ch_set_techno_func_duration(vNCK, chan_Index, techno_type, techno_number, time):
    index = ct.c_long(chan_Index)
    ttype = ct.c_int(techno_type.value)
    number = ct.c_long(techno_number)
    time_us = ct.c_long(time)

    ret = vNCK.kernelv_ch_set_techno_func_duration(
        index, ttype, number, time_us)
    return ret


def ch_set_techno_func_user_ackn(vNCK, chan_Index, techno_type, techno_number):
    index = ct.c_long(chan_Index)
    ttype = ct.c_int(techno_type.value)
    number = ct.c_long(techno_number)

    ret = vNCK.kernelv_ch_set_techno_func_user_ackn(index, ttype, number)
    return ret


def ch_ackn_techno_func(vNCK, chan_Index, techno_type, techno_number):
    index = ct.c_long(chan_Index)
    ttype = ct.c_int(techno_type.value)
    number = ct.c_long(techno_number)

    ret = vNCK.kernelv_ch_ackn_techno_func(index, ttype, number)
    return ret


def ax_ackn_techno_func(vNCK, chan_Index, techno_type, techno_number):
    index = ct.c_long(chan_Index)
    ttype = ct.c_int(techno_type.value)
    number = ct.c_long(techno_number)

    ret = vNCK.kernelv_ax_ackn_techno_func(index, ttype, number)
    return ret


def get_license_info(vNCK):
    pLicenseInfo = LICENSE_INFO()

    ret = vNCK.kernelv_get_license_info(ct.pointer(pLicenseInfo))
    return ret, pLicenseInfo


def set_options(vNCK, options):
    optionsMask = ct.c_long(options)

    ret = vNCK.kernelv_set_options(optionsMask)
    return ret, optionsMask


def ch_get_decoder_positions(vNCK, chan_index):
    index = ct.c_ulong(chan_index)
    ret_buffer = DECODER_POSITIONS()
    ret_Length = ct.c_ulong()

    ret = vNCK.kernelv_ch_get_decoder_positions(
        index, ct.pointer(ret_buffer), 459, ct.byref(ret_Length))
    return ret, ret_buffer.DATA[1].mcs_pos, ret_buffer.HEADER.line_number


def ch_get_prog_start_mode(vNCK, chan_index):
    index = ct.c_ulong(chan_index)
    start_mode = ct.c_int()

    ret = vNCK.kernelv_ch_get_prog_start_mode(index, ct.pointer(start_mode))
    mode = PROG_START_MODE(start_mode.value)
    return ret, mode


def ch_set_cont_visu_grid(vNCK, chan_index, visu_grid):
    index = ct.c_ulong(chan_index)
    grid = ct.c_ulong(visu_grid)

    ret = vNCK.kernelv_ch_set_cont_visu_grid(index, grid)
    return ret


def ch_set_cont_visu_rel_curvature_error(vNCK, chan_index, rel_err):
    index = ct.c_ulong(chan_index)
    rel_error = ct.c_ulong(rel_err)

    ret = vNCK.kernelv_ch_set_cont_visu_rel_curvature_error(index, rel_error)
    return ret


def ch_set_cont_visu_abs_curvature_error(vNCK, chan_index, abs_err):
    index = ct.c_ulong(chan_index)
    abs_error = ct.c_ulong(abs_err)

    ret = vNCK.kernelv_ch_set_cont_visu_abs_curvature_error(index, abs_error)
    return ret


def get_axis_pos_ipo(vNCK, ChNbr, AxIdx):
    port = ct.c_ushort(551)
    indexGroup = ct.c_ulong((int("0x2130"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0x"+str(AxIdx)+"0007", 0))
    length = ct.c_ulong(8)
    data = ct.c_double()
    pdata = ct.c_void_p()

    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_request(
        port, indexGroup, indexOffset, ct.byref(length), pdata)
    return (ret, data.value)


def get_axis_vel_ipo(vNCK, ChNbr, AxNbr):
    port = ct.c_ushort(551)
    indexGroup = ct.c_ulong((int("0x2130"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0x"+str(AxNbr)+"000F", 0))
    length = ct.c_ulong(8)
    data = ct.c_double()
    pdata = ct.c_void_p()

    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_request(
        port, indexGroup, indexOffset, ct.byref(length), pdata)
    return (ret, data.value)


def get_axis_acc_ipo(vNCK, ChNbr, AxIdx):
    port = ct.c_ushort(551)
    indexGroup = ct.c_ulong((int("0x2130"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0x"+str(AxIdx)+"0010", 0))
    length = ct.c_ulong(8)
    data = ct.c_double()
    pdata = ct.c_void_p()

    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_request(
        port, indexGroup, indexOffset, ct.byref(length), pdata)
    return (ret, data.value)


def get_path_vel(vNCK, ChNbr):
    port = ct.c_ushort(551)
    indexGroup = ct.c_ulong((int("0x2130"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0x15", 0))
    length = ct.c_ulong(8)
    data = ct.c_double()
    pdata = ct.c_void_p()

    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_request(
        port, indexGroup, indexOffset, ct.byref(length), pdata)
    return (ret, data.value)


def get_path_vel_max(vNCK, ChNbr):
    port = ct.c_ushort(551)
    indexGroup = ct.c_ulong((int("0x2130"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0xF", 0))
    length = ct.c_ulong(4)
    data = ct.c_uint32()
    pdata = ct.c_void_p()

    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_request(
        port, indexGroup, indexOffset, ct.byref(length), pdata)
    return (ret, data.value)


def get_path_vel_max_trans(vNCK, ChNbr):
    port = ct.c_ushort(551)
    indexGroup = ct.c_ulong((int("0x2130"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0x10", 0))
    length = ct.c_ulong(4)
    data = ct.c_uint32()
    pdata = ct.c_void_p()

    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_request(
        port, indexGroup, indexOffset, ct.byref(length), pdata)
    return (ret, data.value)


def get_path_prg_vel(vNCK, ChNbr):
    port = ct.c_ushort(551)
    indexGroup = ct.c_ulong((int("0x2130"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0x16", 0))
    length = ct.c_ulong(8)
    data = ct.c_double()
    pdata = ct.c_void_p()

    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_request(
        port, indexGroup, indexOffset, ct.byref(length), pdata)
    return (ret, data.value)


def ch_get_cont_visu_data(vNCK, chan_index):
    index = ct.c_ulong(chan_index)
    pData = ct.create_string_buffer(296)
    retlLength = ct.c_ulong()

    ret = vNCK.kernelv_ch_get_cont_visu_data(
        index, ct.pointer(pData), 296, ct.byref(retlLength))

    return ret, retlLength.value, list(pData)


def ch_get_active_g_codes(vNCK, chan_index):
    index = ct.c_ulong(chan_index)
    pGCodes = (ct.c_short*G_GROUP_TYPE.G_MAX_G_GRP.value)()

    ret = vNCK.kernelv_ch_get_active_g_codes(index, ct.pointer(pGCodes))
    return ret, pGCodes


def ch_get_active_g_group(vNCK, g_codes, g_group):
    ttype = ct.c_int(g_group)

    ret = vNCK.kernelv_get_active_g_group(ct.pointer(g_codes), ttype)
    return ret, ttype.value


def ch_get_command_feed(vNCK, chan_index):
    index = ct.c_ulong(chan_index)
    command_feed = ct.c_long()

    ret = vNCK.kernelv_ch_get_command_feed(index, ct.byref(command_feed))
    return ret, command_feed.value


def ch_get_active_feed(vNCK, chan_index):
    index = ct.c_ulong(chan_index)
    active_feed = ct.c_long()

    ret = vNCK.kernelv_ch_get_active_feed(index, ct.byref(active_feed))
    return ret, active_feed.value


def set_call_ratio(vNCK, decoder_calls, interpolat_calls):
    dec_calls = ct.c_ushort(decoder_calls)
    interpolator_calls = ct.c_ushort(interpolat_calls)

    ret = vNCK.kernelv_set_call_ratio(dec_calls, interpolator_calls)
    return ret


def read_error(vNCK):
    ret = vNCK.kernelv_read_error()
    return ret


def get_error_id(vNCK):
    ret = vNCK.kernelv_get_error_id()
    return ret


def get_error_reaction(vNCK):
    ret = vNCK.kernelv_get_error_reaction()
    return ret


def get_error_severity(vNCK):
    ret = vNCK.kernelv_get_error_severity()
    return ret


def get_error_channel(vNCK):
    ret = vNCK.kernelv_get_error_channel()
    return ret


def get_error_message_string(vNCK):
    err_str = ct.create_string_buffer(ERROR_STRING_LEN)
    err_str_length = ct.c_ulong()

    ret = vNCK.kernelv_get_error_message_string(
        ct.byref(err_str), ct.byref(err_str_length))
    sErrString = err_str.value
    ierr_length = err_str_length.value
    return ret, sErrString, ierr_length


def get_error_id_text(vNCK):
    err_str = ct.create_string_buffer(ERROR_STRING_LEN)
    err_str_length = ct.c_ulong()

    ret = vNCK.kernelv_get_error_id_text(
        ct.byref(err_str), ct.byref(err_str_length))
    sErrString = err_str.value
    ierr_length = err_str_length.value
    return ret, sErrString, ierr_length


def get_error_values(vNCK):
    p_values = (ERROR_VALUE*KERNELV_ERROR_VALUE_COUNT)()
    #print('p_values before kernelv:')
    # for i in range(KERNELV_ERROR_VALUE_COUNT):
    #    print('p_values[{}] type:{}, dimension:{}, meaning:{}, fillup:{}, data:{}'.format(i, p_values[i].type, p_values[i].dimension, p_values[i].meaning, p_values[i].fillup, p_values[i].data))
    err_str_length = ct.c_ulong(200)  # sollte eigentlich leer sein?
    ret = vNCK.kernelv_get_error_values(
        ct.pointer(p_values), ct.byref(err_str_length))
    #print('p_values after kernelv:')
    # for i in range(KERNELV_ERROR_VALUE_COUNT):
    #    print('p_values[{}] type:{}, dimension:{}, meaning:{}, fillup:{}, data:{}'.format(i, p_values[i].type, p_values[i].dimension, p_values[i].meaning, p_values[i].fillup, p_values[i].data))
    return ret, p_values, err_str_length.value


def get_error_cycle_time(vNCK):
    ret = vNCK.kernelv_get_error_cycle_time()
    return ret


####################################################################################################################
# testcase schreiben
####################################################################################################################

# sollte eignetlich 0 oder 1 zurück geben. liefert aber negative werte statt 0??
def error_is_program_error(vNCK):
    ret = vNCK.kernelv_error_is_program_error()
    return ret


# wirft nur -28 raus, auch wenn ich errors in das nc packe
def program_error_get_path(vNCK):
    return_str = ct.c_char_p()
    return_length = ct.c_ulong()

    ret = vNCK.kernelv_program_error_get_path(
        ct.byref(return_str), ct.byref(return_length))
    sreturn_str = return_str.value
    lreturn_length = return_length.value
    return ret, sreturn_str, lreturn_length


def program_error_get_file_name(vNCK):  # wirft nur -28 raus
    return_str = ct.c_char_p()
    return_length = ct.c_ulong()

    ret = vNCK.kernelv_program_error_get_file_name(
        ct.byref(return_str), ct.byref(return_length))
    sreturn_str = return_str.value
    lreturn_length = return_length.value
    return ret, sreturn_str, lreturn_length


def program_error_get_fileoffset(vNCK):  # wirft nur -28 raus
    fileoffset = ct.c_ulong()

    ret = vNCK.kernelv_program_error_get_fileoffset(ct.byref(fileoffset))
    return ret, fileoffset.value


def program_error_get_lineoffset(vNCK):  # wirft nur -1 raus
    ret = vNCK.kernelv_program_error_get_lineoffset()
    return ret


def program_error_get_tokenoffset(vNCK):  # wirft nur -1 raus
    ret = vNCK.kernelv_program_error_get_tokenoffset()
    return ret


def program_error_get_linenumber(vNCK):  # wirft nur -1 raus
    line_number = ct.c_ushort()

    ret = vNCK.kernelv_program_error_get_linenumber(ct.byref(line_number))
    return ret, line_number.value

####################################################################################################################

####################################################################################################################


def ch_get_cs_name(vNCK, chan_index, cs_index):
    chanIndex = ct.c_ulong(chan_index)
    csIndex = ct.c_ushort(cs_index)
    name = ct.create_string_buffer(8)
    nameLength = ct.create_string_buffer(8)
    returnLength = ct.c_ulong()

    ret = vNCK.kernelv_ch_get_cs_name(chanIndex, csIndex, ct.byref(
        name), nameLength, ct.byref(returnLength))
    return ret, name.value, returnLength.value


def ch_get_cs_rot_matrix(vNCK, chan_index, cs_index):
    chanIndex = ct.c_ulong(chan_index)
    csIndex = ct.c_ushort(cs_index)
    matrix = ((ct.c_double*3)*3)()
    nameLength = ct.create_string_buffer(72)
    returnLength = ct.c_ulong()

    ret = vNCK.kernelv_ch_get_cs_rot_matrix(
        chanIndex, csIndex, ct.byref(matrix), nameLength, ct.byref(returnLength))
    matrix_array = np.array([matrix])
    return ret,  matrix_array, returnLength.value


def ch_get_cs_count(vNCK, chan_index):
    chanIndex = ct.c_ulong(chan_index)
    count = ct.c_ushort()

    ret = vNCK.kernelv_ch_get_cs_count(chanIndex, ct.byref(count))
    return ret, count.value


def ch_active_cs_index(vNCK, chan_index):
    chanIndex = ct.c_ulong(chan_index)
    csIndex = ct.c_ushort()

    ret = vNCK.kernelv_ch_active_cs_index(chanIndex, ct.byref(csIndex))
    return ret, csIndex.value


def ch_axis_get_offsets(vNCK, chan_index, axis_index, cs_index):
    chanIndex = ct.c_ulong(chan_index)
    axisIndex = ct.c_ulong(axis_index)
    csIndex = ct.c_ushort(cs_index)
    offsets = ct.c_long()
    nameLength = ct.create_string_buffer(8*ct.sizeof(ct.c_long()))
    returnLength = ct.c_ulong()

    ret = vNCK.kernelv_ch_axis_get_offsets(chanIndex, axisIndex, csIndex, ct.byref(
        offsets), nameLength, ct.byref(returnLength))
    print('prints:', chanIndex.value, axisIndex.value, csIndex.value)
    return ret, returnLength.value

# new add function by ISG


def read_act_d_word_ipo_conetxt(vNCK, chan_index):
    """
    get tool number from nc program
    :param vNCK: dll file
    :param chan_index: working channel number in VNCK
    :return ret: int, function execution status
    :return pdata.contents.value: spindle velocity
    """
    ChNbr = chan_index + 1
    port = ct.c_ushort(551)
    indexGroup = ct.c_ulong((int("0x2130"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0x11", 0))
    length = ct.c_ulong()
    data = ct.c_uint()
    #pdata = ct.c_void_p()

    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_req(
        port, indexGroup, indexOffset, ct.byref(length), pdata)
    return ret, pdata.contents.value


def get_spindle_vel_ipo(vNCK, ChNbr, AxNbr):
    """
    get spindle velocity
    :param vNCK: dll file
    :param ChNbr: working channel number in VNCK
    :param AxNbr: spindle axis number
    :return: ret: int, function execution status
    :return: data.value, spindle velocity
    """
    port = ct.c_ushort(551)
    indexGroup = ct.c_ulong((int("0x2530"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0x"+str(AxNbr)+"0021", 0))
    length = ct.c_ulong(8)
    data = ct.c_double()
    pdata = ct.c_void_p()

    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_request(port, indexGroup, indexOffset,
                                         ct.byref(length), pdata)
    return ret, data.value


def get_p_var(vNCK, chan_index, name):
    """
    get p-variable value
    :param vNCK: dll file
    :param chan_index: int, working channel index
    :param name: str, variable name
    :return: ret: int, function execution status
    :return: pdata.contents.value: desired variable value
    """
    ChNbr = chan_index + 1
    port = ct.c_ushort(552)
    indexGroup = ct.c_ulong((int("0x2230"+str(ChNbr), 0)))
    indexOffset = ct.c_ulong(int("0x1C", 0))
    readLength = ct.c_ulong(8)
    writeLength = ct.c_ulong(8)
    var_name = name.encode('utf-8')
    data = ct.create_string_buffer(var_name, 8)
    pdata = ct.c_void_p
    pdata = ct.pointer(data)

    ret = vNCK.kernelv_sync_read_write_request(
        port, indexGroup, indexOffset, ct.byref(readLength), writeLength, ct.byref(data))

    pdata = ct.cast(pdata, POINTER(c_double))

    return ret, pdata.contents.value


def unloadVnck(vNCK):
    kernel32 = ct.WinDLL('kernel32', use_last_error=True)
    kernel32.FreeLibrary.argtypes = [ct.wintypes.HMODULE]
    kernel32.FreeLibrary(vNCK._handle)
