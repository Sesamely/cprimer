"""Please add some notations for this module here"""
#!/usr/bin/env python
# coding=utf-8

from datetime import datetime, timedelta

def to_timesstamp(dt_str, tz_str):
    """   string  """
    time = datetime.strptime(dt_str, '%Y-%m-%d %H:%M:%S')
    deltahours = int(tz_str.split('+')[1].split(':')[0])
    utctime = time - timedelta(hours=deltahours)
    print(datetime.timestamp(utctime))

if __name__ == '__main__':
    dt = input("Like '2015-1-21 9:01:30' ")
    tz = input("Like 'UTC+5:00' ")
    to_timesstamp(dt, tz)
