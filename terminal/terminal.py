import argparse
import numpy as np
from backend import sweep, servo, stop, channel, sweep_r, hsp, show, ref
from csv_reader import get_wfm, tran_wfm
import os.path 
# from json_load import load_settings

def is_file_exists(fname):
    try:
        open(fname)
    except FileNotFoundError as e:
        print('%s: %s' %(e.__class__.__name__,  e))
        return False 
    return True 

def help_action(args):
    subparsers.choices[args.cmd].print_help()

def sweep_action(args):
    sweep(args.ch, args.lower, args.upper, args.step)

def sweep_r_action(args):
    global max_pd, min_pd
    avg_lens = 3
    max_ar = np.zeros(avg_lens)
    min_ar = np.zeros(avg_lens)
    for _ in range(avg_lens):
        print('Sweep', _)
        a = sweep_r(args.ch, args.lower, args.upper, args.step)
        max_ar[_] = int(str(a[0]).split(' ')[3])
        min_ar[_] = int(str(a[1]).split(' ')[3])

    max_pd[args.ch] = int(np.mean(max_ar))
    max_pd_err = np.std(max_ar)/(avg_lens**0.5)

    min_pd[args.ch] = int(np.mean(min_ar))
    min_pd_err = np.std(min_ar)/(avg_lens**0.5)
    print("Max PD mean: {}, Max PD err: {}".format(max_pd,round(max_pd_err,1)))
    print("Min PD mean: {}, Min PD err: {}".format(min_pd,round(min_pd_err,1)))


def servo_p_action(args):
    global max_pd, min_pd

    if not is_file_exists(args.fname):
        return 

    # wrong format f_I
    try:
        f = float(eval(args.f_I.strip('"')))
    except (SyntaxError, NameError, TypeError) as e:
        print('%s: %s' %(e.__class__.__name__,  e))
        return
    if f > 0:
        f = -f
    servo(args.ch, f, args.G, tran_wfm(args.fname, max_pd[args.ch], min_pd[args.ch]))

def ref_p_action(args):
    global max_pd, min_pd
    # non-exising file
    if not is_file_exists(args.fname):
        return 

    ref(args.ch, tran_wfm(args.fname, max_pd[args.ch], min_pd[args.ch]))

def servo_action(args):
    # non-exising file
    if not is_file_exists(args.fname):
        return 

    # wrong format f_I
    try:
        f = float(eval(args.f_I.strip('"')))
    except (SyntaxError, NameError, TypeError) as e:
        print('%s: %s' %(e.__class__.__name__,  e))
        return
    if f > 0:
        f = -f
    servo(args.ch, f, args.G, get_wfm(args.fname))

def ref_action(args):
    # non-exising file
    if not is_file_exists(args.fname):
        return 

    ref(args.ch, get_wfm(args.fname))

def channel_action(args):
    if args.on:
        channel(args.ch, True)
    else:
        channel(args.ch, False)

def hsp_action(args):
    for i, sp in enumerate([args.sp0, args.sp1, args.sp2, args.sp3]):
        if not 0 <= sp <= 1500:
            print("Setpoint for ch%d out of bound: 0 <= sp <= 1500" % i)
            return 
    hsp(args.sp0, args.sp1, args.sp2, args.sp3)

def run_action(args):    
    for ch in [0,1,2,3]:
        if ch != 2:
            ref(ch, get_wfm(os.path.join(args.exp, 'mot_repumper.csv')))
        else:
            ref(ch, get_wfm(os.path.join(args.exp, 'bfield.csv')))


def exit_action(args):
    exit(0)

max_pd = np.zeros(4)
min_pd = np.zeros(4)

parser = argparse.ArgumentParser('', description="Intesnity servo terminal", add_help=False, epilog="Use 'help <command>' to see how to use each command.", )
subparsers = parser.add_subparsers()

sweep_parser = subparsers.add_parser("sweep", description="Start sweep and return averaged low and high PD readings", add_help=False, )
sweep_parser.add_argument('ch', type=int, choices=[0,1,2,3], help='Channel number')
sweep_parser.add_argument('--lower', type=int, required=False, default=0, help='Lower limit of DAC number. Default is 0. ')
sweep_parser.add_argument('--upper', type=int, required=False, default=1500, help='Upper limit of DAC number. Default is 1500')
sweep_parser.add_argument('--step', type=int, required=False, default=1, help='Step size of sweep. Default is 1')
sweep_parser.add_argument('-s', '--single', action='store_true', help='Step size of sweep. Default is 1')
sweep_parser.set_defaults(func=lambda args: sweep_action(args) if args.r else sweep_r_action(args))


servo_parser = subparsers.add_parser("servo", description="Start PI servo", add_help=False, )
servo_parser.add_argument('ch', type=int, choices=[0,1,2,3], help='Channel number')
servo_parser.add_argument('f_I', metavar='f_I', type=str, help='I corner in the unit of Nyquist frequency.')
servo_parser.add_argument('G', metavar='G', type=float, help='Overall gain')
servo_parser.add_argument('fname', metavar='fname', type=str, help='Reference waveform file')
servo_parser.add_argument('-r', help='Raw if set', action='store_true')
servo_parser.set_defaults(func=lambda args: ref_action(args) if args.r else ref_p_action(args))

ref_parser = subparsers.add_parser("ref", description="Update reference", add_help=False, )
ref_parser.add_argument('ch', type=int, choices=[0,1,2,3], help='Channel number')
ref_parser.add_argument('fname', metavar='fname', type=str, help='Reference waveform file')
ref_parser.add_argument('-r', help='Raw if set', action='store_true')
ref_parser.set_defaults(func=lambda args: ref_action(args) if args.r else ref_p_action(args))

channel_parser = subparsers.add_parser("channel", description="Control channel on/off; always clears step count", add_help=False, )
channel_parser.add_argument('ch', type=int, choices=[0,1,2,3], help='Channel number')
on_off = channel_parser.add_mutually_exclusive_group(required=True)
on_off.add_argument('--on', action='store_true')
on_off.add_argument('--off', action='store_true')
channel_parser.set_defaults(func=channel_action)

update_hsp_parser = subparsers.add_parser("hsp", description="Update hold setpoint", add_help=False, )
update_hsp_parser.add_argument('sp0', type=int, help='16-bit number of hold setpoint for ch0')
update_hsp_parser.add_argument('sp1', type=int, help='16-bit number of hold setpoint for ch1')
update_hsp_parser.add_argument('sp2', type=int, help='16-bit number of hold setpoint for ch2')
update_hsp_parser.add_argument('sp3', type=int, help='16-bit number of hold setpoint for ch3')
update_hsp_parser.set_defaults(func=hsp_action)

show_parser = subparsers.add_parser("show", description="Show the contents of the controller", add_help=False, )
show_parser.add_argument('ch', type=int, choices=[0,1,2,3], help='Channel number')
show_parser.set_defaults(func=lambda args:show(args.ch))

run_parser = subparsers.add_parser("run", description="Upload experiment sequence", add_help=False, )
run_parser.add_argument('exp', type=int, choices=[0,1,2,3], help='Folder to experiment, must contain mot_repumper.csv and bfield.csv')
run_parser.set_defaults(func=run_action)

stop_parser = subparsers.add_parser("stop", description="Stop current command", add_help=False, )
stop_parser.set_defaults(func=stop)

exit_parser = subparsers.add_parser("exit", description="Exit terminal", add_help=False, )
exit_parser.set_defaults(func=exit_action)


help_parser = subparsers.add_parser("help",
description='Display help for commands', add_help=False, )
help_parser.add_argument('cmd', type=str, choices=subparsers.choices.keys(), help='command name')
help_parser.set_defaults(func=help_action)

parser.print_help()

prompt = '>>> '
while True:
    commands = input(prompt).split()
    if not len(commands):
        continue
    try:
        a = parser.parse_args(commands)
        a.func(a)
    except argparse.ArgumentError as e:
        print(e)
    except SystemExit as e:
        if not e.code:
            exit(0)
        pass
