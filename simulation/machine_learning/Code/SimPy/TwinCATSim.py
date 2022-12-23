import os
import platform
import sys
import logging
from . import vnck
from datetime import datetime
import time

from .config import TcAdsDll_32_folderpath, TcAdsDll_64_folderpath, kernelv_mt_folderpath, kernelv_mt64_folderpath, \
    startupfile, cycleTime_vnck, channel, data_rootpath, simtoolpath_filename


class TwinCATSim:

    def __init__(self, kernelKey):

        self.prog_path = None
        self.featurefile = None
        self.mydll = None
        datetime_str = datetime.now().strftime("%d%m_%Y")
        # ".\\log\\twincat_" + datetime_str + ".log"
        log_file_path = os.path.join(os.path.dirname(
            __file__), "log", "twincat_" + datetime_str + ".log")
        logging.basicConfig(filename=log_file_path, level=logging.DEBUG)

        # Checks if the System is Windows 32 or 64 Bit and loads the dll + dependencies respectively
        if platform.architecture()[0] == '32bit':
            print('Windows version {}. Loading the {} Version of Kernelv.dll'.format((platform.architecture()[0]),
                                                                                     platform.architecture()[0]))
            if os.path.exists(TcAdsDll_32_folderpath):
                os.add_dll_directory(TcAdsDll_32_folderpath)
            else:
                print(
                    'TcAdsDll.dll could not be found. Please make sure, that the right path is chosen and try again...')

            if os.path.exists(kernelv_mt_folderpath):
                self.mydll = vnck.load(kernelv_mt_folderpath)
            else:
                print(
                    'kernelv_mt.dll could not be found. Please make sure, that the the right path is chosen and try again...')

        elif platform.architecture()[0] == '64bit':
            print('Windows version {}. Loading the {} Version of Kernelv.dll'.format((platform.architecture()[0]),
                                                                                     platform.architecture()[0]))
            if os.path.exists(TcAdsDll_64_folderpath):
                os.add_dll_directory(TcAdsDll_64_folderpath)
            else:
                print(
                    'TcAdsDll.dll could not be found. Please make sure, that the right path is chosen and try again...')

            if os.path.exists(kernelv_mt64_folderpath):
                self.mydll = vnck.load(kernelv_mt64_folderpath)
            else:
                print(
                    'kernelv_mt64.dll could not be found. Please make sure, that the right path is chosen and try again...')

        ret = vnck.startup(self.mydll, cycleTime_vnck, startupfile, kernelKey)

        # if init is not successful show the error code
        if ret != vnck.KERNELV_RETURN.RET_FINISHED.value:
            del self.mydll
            print(
                f"\033[1;31mError occured in initialization of TwinCAT kernel with code: {ret}\033[0m")
            print(
                f"\033[1;33mHint: if error code is -19, please check the license is still avaliable\033[0m")
            # sys.exit()

        print(
            f"[\033[1;32mOK\033[0m]  TwinCAT3 Startup with cycle time \033[1;35m{cycleTime_vnck/1000}ms\033[0m")

    def __del__(self):
        vnck.unloadVnck(self.mydll)
        del self.mydll
        print("[\033[1;32mOK\033[0m]  Shut down TwinCAT3 kernel")

    def read_file(self, partname):
        """
        load NC program
        :param partname: workpiece folder name
        :return: None
        """
        self.prog_path = os.path.join(
            data_rootpath, partname, partname + '.NC')
        if not os.path.exists(self.prog_path):
            print(
                "\033[1;31mERROR: Do not find the input file, please input path again \033[0m")
            exit(-1)

        self.featurefile = os.path.join(
            data_rootpath, partname, simtoolpath_filename)

        print("[\033[1;32mOK\033[0m]   Finding nc program")
        print(
            f"*  The generated tool path will be saved in: \033[1;36m{self.featurefile}\033[0m")

        return partname

    def warmup(self):
        """
        idle mode
        :return: None
        """
        for i in range(100):
            vnck.do_cycle(self.mydll)
            _, error_id, error_msg = vnck.get_error(self.mydll)
            if (error_id != 0):
                print("*  internal error occurred, Id:" + str(error_id))
                logging.error(
                    str(error_id) + error_msg.decode(encoding='utf-8', errors='ignore'))

    def sim(self):
        """
        execute vnck simulation
        :return: None
        """
        fCycle = True
        state = 0
        f_running_prg = False
        outputfile = open(self.featurefile, "w")
        outputfile.write(
            "Timestamp XActPos YActPos ZActPos S1Actrev Actfeed ToolID BlockNr\n")
        curr_time = datetime.now()
        curr_timestamp = time.mktime(
            curr_time.timetuple()) * 1e3 + int(curr_time.microsecond / 1e3)
        while (fCycle):

            # first state, load nc program
            if state == 0:
                ret = vnck.ch_program_start(
                    self.mydll, channel, self.prog_path.encode(), vnck.PROG_START_MODE.NORMAL.value)

                if ret == vnck.KERNELV_RETURN.RET_FINISHED.value:
                    print("[\033[1;32mOK\033[0m]  Load nc programm in TwinCAT")
                    state += 1

                elif ret != vnck.KERNELV_RETURN.RET_BUSY.value:
                    print(
                        f"Error occurred during loading nc program with code: {ret}")
                    sys.exit()
            # second state, get simulation result in each cycle time
            elif state == 1:
                if not f_running_prg:
                    print("[\033[1;32mOK\033[0m]  TwinCAT Simulation start")
                    f_running_prg = True
                _, state_ch = vnck.ch_get_state(self.mydll, channel)

                if state_ch.value == vnck.CHANNEL_STATE.ACTIVE.value:
                    # add getter function in following part to get vnck result in every cycle time
                    # ToDo: please select one of following two tool getter function in the future work
                    _, d_word = vnck.read_act_d_word_ipo_conetxt(
                        self.mydll, channel)
                    # _, tool_id = vnck.get_p_var(self.mydll, channel, "P99")
                    if d_word != 0:
                        _, acs_pos, _ = vnck.get_wcs_command_positions(
                            self.mydll)
                        _, nc_block_nr = vnck.ch_get_blocknumber(
                            self.mydll, channel)
                        _, feed_rate = vnck.ch_get_active_feed(
                            self.mydll, channel)
                        _, s1_act_rev = vnck.get_spindle_vel_ipo(
                            self.mydll, channel, 1)

                        # create timestamp:
                        curr_timestamp = curr_timestamp + 1
                        outputfile.write(
                            "{:d} {:.3f} {:.3f} {:.3f} {:.3f} {:.3f} {:d} {:d} \n".format(
                                int(curr_timestamp),
                                acs_pos[0] / 10000.,
                                acs_pos[1] / 10000.,
                                acs_pos[2] / 10000.,
                                s1_act_rev / (360 * 100.),
                                feed_rate / 1000.,
                                int(d_word),
                                int(nc_block_nr)))

                elif state_ch.value == vnck.CHANNEL_STATE.READY.value:
                    state += 1

                elif state_ch.value == vnck.CHANNEL_STATE.ERROR.value:
                    print(
                        "\033[1;31mERROR: fatal error occurred during the simulation \033[0m")
                    sys.exit()
                else:
                    print(
                        f"unexpected state occurred with channel state {state_ch.value}, please check the log file")

            # third state, program finish
            elif state == 2:
                print("[\033[1;32mOK\033[0m]  TwinCAT simulation finish")
                fCycle = False

            # execute single step simulation
            ret = vnck.do_cycle(self.mydll)

            # check execution status
            if ret != vnck.KERNELV_RETURN.RET_FINISHED.value:
                print(
                    f"\033[1;31mError occurred  during running simulation in TwinCAT kernel with code: {ret}\033[0m")
                sys.exit()

            _, error_id, error_msg = vnck.get_error(self.mydll)
            if (error_id != 0):
                print("*  internal error occurred, Id:" + str(error_id))
                logging.error(
                    str(error_id) + error_msg.decode(encoding='utf-8', errors='ignore'))

        outputfile.close()
