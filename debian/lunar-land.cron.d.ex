#
# Regular cron jobs for the lunar-land package
#
0 4	* * *	root	[ -x /usr/bin/lunar-land_maintenance ] && /usr/bin/lunar-land_maintenance
