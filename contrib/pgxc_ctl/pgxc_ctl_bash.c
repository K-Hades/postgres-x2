/*
 *-----------------------------------------------------------------------
 *
 * pgxc_ctl_bash.c
 *
 *    Bash script body for Postrgres-XC configuration and operation tool.
 *
 * Copyright (c) 2013 Postgres-XC Development Group
 *
 *------------------------------------------------------------------------
 *
 * This file was created by make_signature utility when pgxc_ctl was built.
 *
 * pgxc_ctl uses this bash script to configure postgres-xc and read
 * configuration.
 *
 * This provides users very flexible way to configure their own
 * postgres-xc cluster.  For example, by using extra variables and script,
 * you can save most of your specific hours typing same (or similar)
 * variable values again and again.
 */

#include <stddef.h>

/*
 * Bash script to read pgxc_ctl configuration parameters and write
 * back to itself.
 *
 * This part is written to pgxc_ctl work directory and reads
 * configuration file, which is also written in bash script.
 */

char *pgxc_ctl_bash_script[] = {
"#!/bin/bash",
"# Common variables ######################################################################",
"xc_prompt='PGXC$ '",
"interactive=n",
"verbose=n",
"progname=$0",
"",
"bin=pgxc_ctl		# Just in case.  Never touch this",
"logfile=none",
"",
"#===========================================================",
"#",
"# Extract parsed configuration values",
"#",
"#===========================================================",
"",
"# $1 is variable name of the array to print",
"function print_array",
"{",
"	echo -n $1 \" \"",
"	eval echo '$'{$1[@]}",
"}",
"",
"",
"function print_values",
"{",
"	local i",
"	declare -i i",
"	local el",
"",
"	# Install Directory",
"	echo pgxcInstallDir $pgxcInstallDir",
"",
"	# Overall",
"	echo pgxcOwner $pgxcOwner",
"	echo pgxcUser $pgxcUser",
"	echo tmpDir $tmpDir",
"	echo localTmpDir $localTmpDir",
"	echo configBackup $configBackup",
"	echo configBackupHost $configBackupHost",
"	echo configBackupDir $configBackupDir",
"	echo configBackupFile $configBackupFile",
"",
"	# GTM overall",
"	echo gtmName $gtmName",
"",
"	# GTM master",
"	echo gtmMasterServer $gtmMasterServer",
"	echo gtmMasterPort $gtmMasterPort",
"	echo gtmMasterDir $gtmMasterDir",
"	echo gtmExtraConfig $gtmExtraConfig",
"	echo gtmMasterSpecificExtraConfig $gtmMasterSpecificExtraConfig",
"",
"	# GTM slave",
"	echo gtmSlave $gtmSlave",
"	echo gtmSlaveServer $gtmSlaveServer",
"	echo gtmSlavePort $gtmSlavePort",
"	echo gtmSlaveDir $gtmSlaveDir",
"	echo gtmSlaveSpecificExtraConfig $gtmSlaveSpecificExtraConfig",
"",
"	# GTM Proxy",
"	echo gtmProxy $gtmProxy",
"	print_array gtmProxyNames",
"	print_array gtmProxyServers",
"	print_array gtmProxyPorts",
"	print_array gtmProxyDirs",
"	echo gtmPxyExtraConfig $gtmPxyExtraConfig",
"	print_array gtmPxySpecificExtraConfig",
"",
"	# Coordinators overall",
"	print_array coordNames",
"	print_array coordPorts",
"	print_array poolerPorts",
"	print_array coordPgHbaEntries",
"",
"	# Coordinators master",
"	print_array coordMasterServers",
"	print_array coordMasterDirs",
"	print_array coordMaxWALSenders",
"",
"	# Coordinators slave",
"	echo coordSlave $coordSlave",
"	echo coordSlaveSync $coordSlaveSync",
"	print_array coordSlaveServers",
"	print_array coordSlaveDirs",
"	print_array coordArchLogDirs",
"",
"	# Coordinator Configuration files",
"	echo coordExtraConfig $coordExtraConfig",
"	print_array coordSpecificExtraConfig",
"	echo coordExtraPgHba $coordExtraPgHba",
"	print_array coordSpecificExtraPgHba",
"",
"	# Coordinator Additional Slaves",
"	echo coordAdditionalSlaves $coordAdditionalSlaves",
"	if [ \"$coordAdditionalSlaves\" == \"y\" ]; then",
"		print_array coordAdditionalSlaveSet",
"		for ((i=0; i<${#coordAdditionalSlaveSet[@]}; i++)); do",
"			el=${coordAdditionalSlaveSet[$i]}",
"			echo -n ${el}_Sync \" \"",
"			eval echo '$'\"$el\"_Sync",
"			print_array ${el}_Servers",
"			print_array ${el}_Dirs",
"			print_array ${el}_ArchLogDirs",
"		done",
"	fi",
"",
"	# Datanodes overall",
"	echo primaryDatanode $primaryDatanode",
"	print_array datanodeNames",
"	print_array datanodePorts",
"	print_array datanodePgHbaEntries",
"	",
"	# Datanodes masters",
"	print_array datanodeMasterServers",
"	print_array datanodeMasterDirs",
"	print_array datanodeMaxWALSenders",
"	",
"	# Datanodes slaves",
"	echo datanodeSlave $datanodeSlave",
"	echo datanodeSlaveSync $datanodeSlaveSync",
"	print_array datanodeSlaveServers",
"	print_array datanodeSlaveDirs",
"	print_array datanodeArchLogDirs",
"",
"	# Datanode configuration files",
"	echo datanodeExtraConfig $datanodeExtraConfig",
"	print_array datanodeSpecificExtraConfig",
"	echo datanodeExtraPgHba $datanodeExtraPgHba",
"	print_array datanodeSpecificExtraPgHba",
"",
"	# Datanodes additional slaves",
"	echo datanodeAdditionalSlaves $datanodeAdditionalSlaves",
"	if [ \"$datanodeAdditionalSlaves\" == \"y\" ]; then",
"		print_array datanodeAdditionalSlaveSet",
"		for ((i=0; i<${#datanodeAdditionalSlaveSet[@]}; i++)); do",
"			el=${datanodeAdditionalSlaveSet[$i]}",
"			echo -n ${el}_Sync \" \"",
"			eval echo '$'\"$el\"_Sync",
"			print_array ${el}_Servers",
"			print_array ${el}_Dirs",
"			print_array ${el}_ArchLogDirs",
"		done",
"	fi",
"	",
"	# WAL Archives",
"	echo walArchive $walArchive",
"	print_array walArchiveSet",
"	if [ \"$walArchive\" == \"y\" ]; then",
"		for ((i=0; i<${#walArchvieSet[@]}; i++)); do",
"			print_array ${el}_source",
"			echo -n ${el}_host",
"			eval echo '$'\"$el\"_host",
"			echo -n ${el}_backupdir",
"			eval echo '$'\"$el\"_backupdir",
"		done",
"	fi",
"}",
"",
"",
"",
"#============================================================",
"#",
"# Common functions",
"#",
"#============================================================",
"",
"# Optionally $1 will be $PGXC_CTL_HOME settings.",
"function set_home",
"{",
"	if [ $# > 1 ]; then",
"		echo \"Invalid set_home function call\"",
"		return 1",
"	fi",
"	if [ $# == 1 ]; then",
"		if [ -d $1 ]; then",
"			pgxc_ctl_home=$1",
"		else",
"			eecho \"set_home: $1 is not a directory.\"",
"			return 1",
"		fi",
"	elif [ $PGXC_CTL_HOME != \"\" ]; then",
"		if [ -d $PGXC_CTL_HOME ]; then",
"			pgxc_ctl_home=$PGXC_CTL_HOME",
"		else",
"			eecho \"set_home: env PGXC_CTL_HOME($PGXC_CTL_HOME) is not a directory.\"",
"			return 1;",
"		fi",
"	fi",
"	cd $pgxc_ctl_home;",
"}",
"",
"###############################################################################",
"#",
"#   EXECUTING SECTION",
"#",
"###############################################################################",
"",
"#=======================================================",
"# Things to be done at first",
"#=======================================================",
"",
"# Handle options",
"progname=$0",
"moretodo=y",
"cmd_with_log=null",
"#set_home",
"if [ -f $pgxc_ctl_home/.pgxc_ctl_rc ]; then",
"	source $pgxc_ctl_home/.pgxc_ctl_rc",
"fi",
"",
"configFile=\"\"",
"",
"while [ $moretodo == y ]; do",
"	if [ $# -gt 0 ]; then",
"		case $1 in",
"			-v )",
"				shift;",
"				verbose=y;",
"				continue;;",
"			--verbose )",
"				shift;",
"				verbose=y;",
"				continue;;",
"			--silent )",
"				verbose=n;",
"				continue;;",
"			-d ) # debug option",
"				shift;",
"				DEBUG=y;",
"				continue;;",
"			--debug )",
"				shift;",
"				DEBUG=y;",
"				continue;;",
"			-c ) # Configuraton file",
"				shift;",
"				if [ $# -le 0 ]; then",
"					echo ERROR: no -c option value found",
"					exit 1",
"				else",
"					configFile=$1",
"					shift",
"				fi;",
"				continue;;",
"			--configuration ) # Configuraion file",
"				shift;",
"				if [ $# -le 0 ]; then",
"					echo ERROR: no --configuration option value found",
"					exit 1",
"				else",
"					configFile=$1",
"					shift",
"				fi;",
"				continue;;",
"			--home ) # PGXC_CTL_HOME",
"				shift;",
"				if [ $# -le 0 ]; then",
"					echo ERROR: no pgxc_ctl_home specified",
"					exit 1",
"				else",
"					pgxc_ctl_home=$1",
"					cd $pgxc_ctl_home",
"					shift",
"				fi;",
"				continue;;",
"			--signature ) # Check signature",
"				shift;",
"				if [ $# -le 0 ]; then",
"					echo ERROR: Signature does not match",
"					exit 1",
"				fi",
"				if [ \"$1\" != \"$signature\" ]; then",
"					echo ERROR: Signature does not match",
"					exit 1",
"				fi",
"				shift",
"				continue;;",
"			* )",
"				moretodo=n",
"				continue;;",
"		esac",
"	else",
"		moretodo=n",
"	fi",
"done",
"",
"echo $signature",
"# Read configuration file --> Should be activated only when debug option is off",
"",
"if [ -f $pgxc_ctl_home/pgxc_ctl_rc ]; then",
"	source $pgxc_ctl_home/pgxc_ctl_rc",
"fi",
"",
"if [ \"$configFile\" != \"\" ] && [ -f \"$configFile\" ]; then",
"	source $configFile",
"fi",
"# Log option can be overridden by command-line option",
"",
"print_values",
"",
"",
NULL
};

/*
 * Prototype of pgxc_ctl configuration file.
 *
 * It should be self descripting.   Can be extracted to your pgxc_ctl
 * work directory with 'prepare config' command.
 */

char *pgxc_ctl_conf_prototype[] = {
"#!/bin/bash",
"#",
"# Postgres-XC Configuration file for pgxc_ctl utility. ",
"#",
"# Configuration file can be specified as -c option from pgxc_ctl command.",
"# Default is $PGXC_CTL_HOME/pgxc_ctl.org.",
"#",
"# This is bash script so you can make any addition for your convenience to",
"# configure your Postgres-XC cluster.",
"#",
"# Please understand that pgxc_ctl provides only a subset of configuration",
"# which pgxc_ctl provide.  Here's several several assumptions/restrictions",
"# pgxc_ctl depends on.",
"#",
"# 1) All the resources of pgxc nodes has to be owned by the same user.",
"#    Same user means user with the same user name.  User ID may be",
"#    different from server to server.  This must be specified as a",
"#    variable $pgxcOwner.",
"#",
"# 2) All the servers must be reachable via ssh without password.",
"#    It is highly recommended to setup key-based authentication among",
"#    all the servers.",
"#",
"# 3) All the databases in coordinator/datanode has at least one same",
"#    superuser.  Pgxc_ctl uses this user to connect to coordinators",
"#    and datanodes.   Again, no password should be used to connect.",
"#    You have many options to do this, pg_hba.conf, pg_ident.conf and",
"#    others.  Pgxc_ctl provides a way to configure pg_hba.conf but",
"#    not pg_ident.conf.   This will be implemented in the later releases.",
"#",
"# 4) Gtm master and slave can have different port to listen, while",
"#    coordinator and datanode slave should be assigned the same port",
"#    number as master.",
"#",
"# 5) Port number of a coordinator slave must be the same as its master.",
"#",
"# 6) Master and slave are connected using synchronous replication.",
"#    Asynchronous replication have slight (almost none) chance to",
"#    bring total cluster into inconsistent state.",
"#    This chance is very low and may be negligible.  Support of",
"#    asynchronous replication may be supported in the later release.",
"#",
"# 7) Each coordinator and datanode can have only one slave each.",
"#    Cascaded replication and multiple slave are not supported",
"#    in the current pgxc_ctl.",
"#",
"# 8) Killing nodes may end up with IPC resource leak, such as",
"#    semaphore and shared memory.  Only listening port (socket)",
"#    will be cleaned with clean command.",
"#",
"# 9) Backup and restore are not supported in pgxc_ctl at present.",
"#    This is a big task and may need considerable resource.",
"#",
"#=================================================================",
"#",
"#",
"# pgxcInstallDir variable is needed if you invoke \"deploy\" command",
"# from pgxc_ctl utility.  If don't you don't need this variable.",
"pgxcInstallDir=$HOME/pgxc",
"#---- OVERALL ----------------------------------------------------",
"#",
"pgxcOwner=koichi		# owner of the Postgres-XC database cluster.",
"						# Here, we use this both as linux user and",
"						# database user.  This must be the super",
"						# user of each coordinator and datanode.",
"pgxcUser=$pgxcOwner		# OS user of Postgres-XC owner",
"",
"tmpDir=/tmp				# temporary dir used in XC servers",
"localTmpDir=$tmpDir		# temporary dir used here locally",
"",
"configBackup=n				# If you want config file backup,",
"							# specify y to this value.",
"configBackupHost=pgxc-linker	# host to backup config file",
"configBackupDir=$HOME/pgxc		# Backup directory",
"configBackupFile=pgxc_ctl.bak	# Backup file name --> Need to",
"								# synchronize when original changed.",
"",
"#---- GTM ---------------------------------------------------------",
"",
"# GTM is mandatory.  You must have at least (and only) one GTM",
"# master in your Postgres-XC cluster.  If GTM crashes and you need",
"# to reconfigure it, you can do it by pgxc_update_gtm command to",
"# update GTM master with others.   Of course, we provide pgxc_remove_gtm",
"# command to remove it.  This command will not stop the current GTM.",
"# It is up to the operator.",
"",
"#---- Overall -------",
"gtmName=gtm",
"",
"#---- GTM Master -----------------------------------------------",
"",
"#---- Overall ----",
"gtmMasterServer=node13",
"gtmMasterPort=20001",
"gtmMasterDir=$HOME/pgxc/nodes/gtm",
"",
"#---- Configuration ---",
"gtmExtraConfig=none		# Will be added gtm.conf for both Master and",
"						# Slave (done at initialization only)",
"gtmMasterSpecificExtraConfig=none	# Will be added to Master's",
"									# gtm.conf",
"									# (done at initialization only)",
"",
"#---- GTM Slave ---------------------------------------------",
"",
"# Because GTM is a key component to maintain database consistency,",
"# you may want to configure GTM slave for backup.",
"",
"#---- Overall ------",
"gtmSlave=y			# Specify y if you configure GTM Slave.   Otherwise,",
"					# GTM slave will not be configured and all the",
"					# following variables will be reset.",
"gtmSlaveServer=node12	# value none means GTM slave is not available.",
"						# Give none if you don't configure GTM Slave.",
"gtmSlavePort=20001		# Not used if you don't configure GTM slave.",
"gtmSlaveDir=$HOME/pgxc/nodes/gtm	# Not used if you don't configure",
"									# GTM slave.",
"# Please note that when you have GTM failover, then there will be no",
"# slave available until you configure the slave",
"# again. (pgxc_add_gtm_slave function will handle it)",
"",
"#---- Configuration ----",
"gtmSlaveSpecificExtraConfig=none # Will be added to Slave's gtm.conf",
"								 # (done at initialization only)",
"",
"#---- GTM Proxy --------------------------------------------",
"# GTM proxy will be selected based upon which server each component",
"# runs on.  When fails over to the slave, the slave inherits its",
"# master's gtm proxy.  It should be reconfigured based upon the",
"# new location.",
"#",
"# To do so, slave should be restarted.   So pg_ctl promote -> (edit postgresql.conf and recovery.conf) -> pg_ctl restart",
"#",
"# You don't have to configure GTM Proxy if you don't configure GTMslave",
"# or you are happy if every component connects to GTM Master directly.",
"# If you configure GTL slave, you must configure GTM proxy too.",
"",
"#---- Shortcuts ------",
"gtmProxyDir=$HOME/pgxc/nodes/gtm_pxy",
"",
"#---- Overall -------",
"gtmProxy=y		# Specify y if you configure at least one GTM proxy.",
"				# You may not configure gtm proxies",
"				# only when you don't configure GTM slaves.",
"				# If you specify this value not to y, the following",
"				# parameters will be set to default empty values.",
"				# If we find there're no valid Proxy server names",
"				# (means, every servers are specified",
"				# as none), then gtmProxy value will be set to \"n\"",
"				# and all the entries will be set to",
"				# empty values.",
"gtmProxyNames=(gtm_pxy1 gtm_pxy2 gtm_pxy3 gtm_pxy4)",
"				# No used if it is not configured",
"gtmProxyServers=(node06 node07 node08 node09)",
"				# Specify none if you don't configure it.",
"gtmProxyPorts=(20001 20001 20001 20001)",
"				# Not used if it is not configured.",
"gtmProxyDirs=($gtmProxyDir $gtmProxyDir $gtmProxyDir $gtmProxyDir)",
"				# Not used if it is not configured.",
"",
"#---- Configuration ----",
"gtmPxyExtraConfig=none	# Extra configuration parameter for gtm_proxy.",
"						# Coordinator section has an example.",
"gtmPxySpecificExtraConfig=(none none none none)",
"",
"#---- Coordinators ------------------------------------------",
"",
"#---- shortcuts ----------",
"coordMasterDir=$HOME/pgxc/nodes/coord",
"coordSlaveDir=$HOME/pgxc/nodes/coord_slave",
"coordArchLogDir=$HOME/pgxc/nodes/coord_archlog",
"",
"#---- Overall ------------",
"coordNames=(coord1 coord2 coord3 coord4)",
"				# Master and slave use the same name",
"coordPorts=(20004 20005 20004 20005)",
"				# Master and slave use the same port",
"poolerPorts=(20010 20011 20010 20011)",
"				# Master and slave use the same pooler port",
"coordPgHbaEntries=(192.168.1.0/24)",
"				# Assumes that all the coordinator (master/slave) accepts",
"				# the same connection.  This entry allows only $pgxcOwner",
"				# to connect.  If you'd like to setup another connection,",
"				# you should supply these entries through files specified",
"				# below.",
"# Note: The above parameter is extracted as \"host all all 0.0.0.0/0 trust\".",
"# If you don't want",
"# such setups, specify the value () to this variable and supply what you",
"# want using coordExtraPgHba",
"# and/or coordSpecificExtraPgHba variables.",
"",
"#---- Master -------------",
"coordMasterServers=(node06 node07 node08 node09)",
"			# none means this master is not available",
"coordMasterDirs=($coordMasterDir $coordMasterDir $coordMasterDir $coordMasterDir)",
"coordMaxWALsernder=5",
"			# max_wal_senders: needed to configure slave.",
"			# If zero value is specified, it is expected to supply",
"			# this parameter explicitly by external files specified",
"			# in the following.	If you don't configure slaves, leave",
"			#this value to zero.",
"coordMaxWALSenders=($coordMaxWALsernder $coordMaxWALsernder $coordMaxWALsernder $coordMaxWALsernder)",
"			# max_wal_senders configuration for each coordinator.",
"",
"#---- Slave -------------",
"coordSlave=y	# Specify y if you configure at least one coordinator slave.",
"				# Otherwise, the following configuration parameters will be",
"				# set to empty values.  If no effective server names are",
"				# found (that is, every servers are specified as none),",
"				# then coordSlave value will be set to n and all the",
"				# following values will be set to empty values.",
"coordSlaveSync=y	# Specify to connect with synchronized mode.",
"coordSlaveServers=(node07 node08 node09 node06)",
"				# none means this slave is not available",
"coordSlaveDirs=($coordSlaveDir $coordSlaveDir $coordSlaveDir $coordSlaveDir)",
"coordArchLogDirs=($coordArchLogDir $coordArchLogDir $coordArchLogDir $coordArchLogDir)",
"",
"#---- Configuration files---",
"# Need these when you'd like setup specific non-default configuration ",
"# These files will go to corresponding files for the master.",
"# You may supply your bash script to setup extra config lines and extra",
"# pg_hba.conf entries. Or you may supply these files manually.",
"coordExtraConfig=coordExtraConfig",
"				# Extra configuration file for coordinators.  ",
"				# This file will be added to all the coordinators'",
"				# postgresql.conf",
"# Please note that the following sets up minimum parameters which you may",
"# want to change.  You can put your postgresql.conf lines here.",
"cat > $coordExtraConfig <<EOF",
"#================================================",
"# Added to all the coordinator postgresql.conf",
"# Original: $coordExtraConfig",
"log_destination = 'stderr'",
"logging_collector = on",
"log_directory = 'pg_log'",
"listen_addresses = '*'",
"max_connections = 100",
"EOF",
"",
"# Additional Configuration file for specific coordinator master.",
"# You can define each setting by similar means as above.",
"coordSpecificExtraConfig=(none none none none)",
"coordExtraPgHba=none	# Extra entry for pg_hba.conf.  This file will be",
"						# added to all the coordinators' pg_hba.conf",
"coordSpecificExtraPgHba=(none none none none)",
"",
"#----- Additional Slaves -----",
"#",
"# Please note that this section is just a suggestion how we extend the",
"# configuration for multiple and cascaded replication.   They're not used",
"#in the current version.",
"#",
"coordAdditionalSlaves=n	",
"				# Additional slave can be specified as follows: where you",
"coordAdditionalSlaveSet=(cad1)",
"				# Each specifies set of slaves.   This case, two set of",
"				# slaves are configured",
"cad1_Sync=n		# All the slaves at \"cad1\" are connected with asynchronous",
"				# mode.  If not, specify \"y\"",
"				# The following lines specifies detailed configuration fo",
"				# each slave tag, cad1.  You can define cad2 similarly.",
"cad1_Servers=(node08 node09 node06 node07)	# Hosts",
"cad1_dir=$HOME/pgxc/nodes/coord_slave_cad1",
"cad1_Dirs=($cad1_dir $cad1_dir $cad1_dir $cad1_dir)",
"cad1_ALDir=$HOME/pgxc/nodes/coord_archlog_cad1",
"cad1_ArchLogDirs=($cad1_ALDir $cad1_ALDir $cad1_ALDir $cad1_ALDir)",
"",
"",
"#---- Datanodes ---------------------",
"",
"#---- Shortcuts --------------",
"dnMstrDir=$HOME/pgxc/nodes/dn_master",
"dnSlvDir=$HOME/pgxc/nodes/dn_slave",
"dnALDir=$HOME/pgxc/nodes/datanode_archlog",
"",
"#---- Overall ---------------",
"#primaryDatanode=datanode1				# Primary Node.",
"# At present, xc has a problem to issue ALTER NODE against the primary node.",
"# Until it is fixed, the test will be done without this feature.",
"primaryDatanode=datanode1				# Primary Node.",
"datanodeNames=(datanode1 datanode2 datanode3 datanode4)",
"datanodePorts=(20008 20009 20008 20009)	# Master and slave use the same port!",
"datanodePgHbaEntries=(192.168.1.0/24)",
"				# Assumes that all the coordinator (master/slave) accepts",
"				# the same connection. This list sets up pg_hba.conf for",
"				# $pgxcOwner user.  If you'd like to setup other entries,",
"				# supply them through extra configuration files specified",
"				# below.  Note: The above parameter is extracted as \"host",
"				# all all 0.0.0.0/0 trust\".   If you don't want",
"				# such setups, specify the value () to this variable and",
"				# supply what you want using datanodeExtraPgHba",
"				# and/or datanodeSpecificExtraPgHba variables.",
"",
"#---- Master ----------------",
"datanodeMasterServers=(node06 node07 node08 node09)",
"				# none means this master is not available.",
"				# This means that there should be the master but is down.",
"				# The cluster is not operational until the master is",
"				# recovered and ready to run.	",
"datanodeMasterDirs=($dnMstrDir $dnMstrDir $dnMstrDir $dnMstrDir)",
"dnWALSndr=5		# max_wal_senders: needed to configure slave. If zero value is ",
"				# specified, it is expected this parameter is explicitly",
"				# supplied by external configuration files.  If you don't",
"				# configure slaves, leave this value zero.",
"datanodeMaxWALSenders=($dnWALSndr $dnWALSndr $dnWALSndr $dnWALSndr)",
"				# max_wal_senders configuration for each datanode",
"",
"#---- Slave -----------------",
"datanodeSlave=y		# Specify y if you configure at least one coordinator",
"					# slave.  Otherwise, the following configuration",
"					# parameters will be set to empty values.  If no",
"					# effective server names are found (that is, every",
"					# servers are specified as none), then datanodeSlave",
"					# value will be set to n and all the following values",
"					# will be set to empty values.",
"datanodeSlaveServers=(node07 node08 node09 node06)",
"					# value none means this slave is not available",
"datanodeSlaveSync=y		# If datanode slave is connected in synchronized mode",
"datanodeSlaveDirs=($dnSlvDir $dnSlvDir $dnSlvDir $dnSlvDir)",
"datanodeArchLogDirs=( $dnALDir $dnALDir $dnALDir $dnALDir )",
"",
"# ---- Configuration files ---",
"# You may supply your bash script to setup extra config lines and extra",
"# pg_hba.conf entries here.  These files will go to corresponding files for",
"# the master.  Or you may supply these files manually.",
"datanodeExtraConfig=none",
"					# Extra configuration file for datanodes.  This file will",
"					# be added to all the datanodes' postgresql.conf",
"datanodeSpecificExtraConfig=(none none none none)",
"datanodeExtraPgHba=none		# Extra entry for pg_hba.conf.  This file will",
"							# be added to all the datanodes' postgresql.conf",
"datanodeSpecificExtraPgHba=(none none none none)",
"",
"#----- Additional Slaves -----",
"datanodeAdditionalSlaves=n	# Additional slave can be specified as follows:",
"							# where you datanodeAdditionalSlaveSet=(dad1 dad2)",
"							# Each specifies set of slaves.   This case,",
"							#two set of slaves are configured",
"# dad1_Sync=n		  		# All the slaves at \"cad1\" are connected with",
"							# asynchronous mode.  If not, specify \"y\"",
"							# The following lines specifies detailed",
"							# configuration for each slave tag, cad1.",
"							# You can define cad2 similarly.",
"# dad1_Servers=(node08 node09 node06 node07)	# Hosts",
"# dad1_dir=$HOME/pgxc/nodes/coord_slave_cad1",
"# dad1_Dirs=($cad1_dir $cad1_dir $cad1_dir $cad1_dir)",
"# dad1_ALDir=$HOME/pgxc/nodes/coord_archlog_cad1",
"# dad1_ArchLogDirs=($cad1_ALDir $cad1_ALDir $cad1_ALDir $cad1_ALDir)",
"",
"#---- WAL archives ------------------------------------",
"walArchive=n	# If you'd like to configure WAL archive, edit this",
"				# section.  Pgxc_ctl assumes that if you configure WAL",
"				# archive, you configure it for all the coordinators",
"				# and datanodes.  Default is \"no\".   Please specify \"y\"",
"				# here to turn it on.",
"#",
"#		End of Configuration Section",
"#",
"#=====================================================",
"",
"#====================================================",
"# The following is for extension.  Just demonstrate how to write such",
"# extension.  There's no code which takes care of them so please ignore",
"# the following lines.  They are simply ignored by pgxc_ctl.",
"# No side effects.",
"#==========<< Beginning of future extension demonstration >> ===========",
"# You can setup more than one backup set for various purposes, such as",
"# disaster recovery.",
"walArchiveSet=(war1 war2)",
"war1_source=(master)	# you can specify master, slave or another additional",
"						# slaves as a source of WAL archive.  Default is the",
"						# master",
"wal1_source=(slave)",
"wal1_source=(additional_coordinator_slave_set additional_datanode_slave_set)",
"war1_host=node10	# All the nodes are backed up at the same host for",
"					# a given archive set",
"war1_backupdir=$HOME/pgxc/backup_war1",
"wal2_source=(master)",
"war2_host=node11",
"war2_backupdir=$HOME/pgxc/backup_war2",
"#=====<< End of future extension demonstration >> ==============",
NULL
};