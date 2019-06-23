function headerBlock {
	l=${#1}
	printf "${BLUE}%s\n%s\n%s\n" "--${1//?/-}--" "${GREEN}- $1 -${BLUE}" "--${1//?/-}--${NORMAL}"
}

function lineBreak {
	echo -e "${MAGENTA}-=========================================================================-${NORMAL}"
}

function givemeayes {
	echo -n "$1 (y/N)"
	read answer
	    case "$answer" in
	    Y|y|yes|YES|Yes) return 0 ;;
	    *) return 1 ;;
	    esac
}

function stepcheck {
	if (($unattended > 0)); then
		return 0;
	fi

	step=$1
	lineBreak
	if givemeayes "${BRIGHT}Vamos a Instalar : ${step} ?${NORMAL}"; then
		return 0;
	else
		echo -e "\n${YELLOW}OK ${RED}${step}${YELLOW} no lo instalamos...\n${NORMAL}"
		return 1;
	fi

	read answer
	    case "$answer" in
	    Y|y|yes|YES|Yes) return 0 ;;
	    *) echo -e "\n${RED}OK : nos saltamos este paso \n${NORMAL}"; return 1 ;;
	    esac
}


function Ajustes_php(){
	
	sed -i -e 's/max_execution_time = 30/max_execution_time = 300/g' /opt/cpanel/ea-php72/root/etc/php.ini
	sed -i -e 's/max_execution_time = 30/max_execution_time = 300/g' /opt/cpanel/ea-php71/root/etc/php.ini
	sed -i -e 's/max_execution_time = 30/max_execution_time = 300/g' /opt/cpanel/ea-php70/root/etc/php.ini
	sed -i -e 's/max_execution_time = 30/max_execution_time = 300/g' /opt/cpanel/ea-php56/root/etc/php.ini

	sed -i -e 's/max_input_time = 60/max_input_time = 600/g' /opt/cpanel/ea-php72/root/etc/php.ini
	sed -i -e 's/max_input_time = 60/max_input_time = 600/g' /opt/cpanel/ea-php71/root/etc/php.ini
	sed -i -e 's/max_input_time = 60/max_input_time = 600/g' /opt/cpanel/ea-php70/root/etc/php.ini
	sed -i -e 's/max_input_time = 60/max_input_time = 600/g' /opt/cpanel/ea-php56/root/etc/php.ini

	sed -i -e 's/; max_input_vars = 100/max_input_vars = 1000/g' /opt/cpanel/ea-php72/root/etc/php.ini
	sed -i -e 's/; max_input_vars = 100/max_input_vars = 1000/g' /opt/cpanel/ea-php71/root/etc/php.ini
	sed -i -e 's/; max_input_vars = 100/max_input_vars = 1000/g' /opt/cpanel/ea-php70/root/etc/php.ini
	sed -i -e 's/; max_input_vars = 100/max_input_vars = 1000/g' /opt/cpanel/ea-php56/root/etc/php.ini

	sed -i -e 's/memory_limit = 128M/memory_limit = 320M/g' /opt/cpanel/ea-php72/root/etc/php.ini
	sed -i -e 's/memory_limit = 128M/memory_limit = 320M/g' /opt/cpanel/ea-php71/root/etc/php.ini
	sed -i -e 's/memory_limit = 128M/memory_limit = 320M/g' /opt/cpanel/ea-php70/root/etc/php.ini
	sed -i -e 's/memory_limit = 128M/memory_limit = 320M/g' /opt/cpanel/ea-php56/root/etc/php.ini

	sed -i -e 's/post_max_size = 8M/post_max_size = 80M/g' /opt/cpanel/ea-php72/root/etc/php.ini
	sed -i -e 's/post_max_size = 8M/post_max_size = 80M/g' /opt/cpanel/ea-php71/root/etc/php.ini
	sed -i -e 's/post_max_size = 8M/post_max_size = 80M/g' /opt/cpanel/ea-php70/root/etc/php.ini
	sed -i -e 's/post_max_size = 8M/post_max_size = 80M/g' /opt/cpanel/ea-php56/root/etc/php.ini

	sed -i -e 's/upload_max_filesize = 2M/upload_max_filesize = 20M/g' /opt/cpanel/ea-php72/root/etc/php.ini
	sed -i -e 's/upload_max_filesize = 2M/upload_max_filesize = 20M/g' /opt/cpanel/ea-php71/root/etc/php.ini
	sed -i -e 's/upload_max_filesize = 2M/upload_max_filesize = 20M/g' /opt/cpanel/ea-php70/root/etc/php.ini
	sed -i -e 's/upload_max_filesize = 2M/upload_max_filesize = 20M/g' /opt/cpanel/ea-php56/root/etc/php.ini


}

function Compilar_EasyApache(){
	/usr/local/bin/ea_install_profile --install app/shoota.json
}

function Best_TweakSettings(){
	whmapi1 set_tweaksetting key=alwaysredirecttossl value=0 > /dev/null
	whmapi1 set_tweaksetting key=requiressl value=0 > /dev/null
}


function mysql_best_config(){
cat << 'EOF' > /etc/my.cnf
#Reglas de MySQL
[mysqld]
max_connections = 500
query_cache_type =1
query_cache_limit = 2M
query_cache_size = 64M
join_buffer_size = 1M
tmp_table_size = 128M
max_heap_table_size = 128M
table_open_cache = 400
#key_buffer = 2048M
key_buffer_size = 2048M
innodb_buffer_pool_size = 2048M
#Best Practices Reference
open_files_limit=10000
max_allowed_packet=268435456
myisam_sort_buffer_size = 128M
read_buffer_size = 1M
sort_buffer_size = 2M
EOF
}

function hardering_kernel(){
	/sbin/sysctl -w "net.ipv4.tcp_syncookies=1"
	/sbin/sysctl -w "kernel.exec-shield=1"
	/sbin/sysctl -w "kernel.randomize_va_space=1"
	/sbin/sysctl -w "kernel.randomize_va_space=1"
	/sbin/sysctl -w "net.ipv4.conf.all.rp_filter=1"
	/sbin/sysctl -w "net.ipv4.conf.lo.rp_filter=1"
	/sbin/sysctl -w "net.ipv4.conf.eth0.rp_filter=1"
	/sbin/sysctl -w "net.ipv4.conf.default.rp_filter=1"
	/sbin/sysctl -w "net.ipv4.icmp_echo_ignore_broadcasts=1"
	/sbin/sysctl -w "net.ipv4.conf.all.accept_redirects=0"
	/sbin/sysctl -w "net.ipv4.conf.all.send_redirects=0"
	/sbin/sysctl -w "net.ipv4.tcp_sack=0"
	/sbin/sysctl -w "net.ipv4.ip_forward=0"
	/sbin/sysctl -w "net.ipv4.conf.all.accept_source_route=0"
	/sbin/sysctl -w "net.ipv4.conf.lo.accept_source_route=0"
	/sbin/sysctl -w "net.ipv4.conf.eth0.accept_source_route=0"
	/sbin/sysctl -w "net.ipv4.conf.default.accept_source_route=0"
	/sbin/sysctl -w "net.ipv4.tcp_fin_timeout=15"
	/sbin/sysctl -w "net.ipv4.tcp_keepalive_time=7200"
	/sbin/sysctl -p
}


function disable_service(){
	cd /root
for service in \
   avahi-daemon \
   avahi-dnsconfd \
   bluetooth \
   capi \
   conman \
   cpus \
   irda \
   lisa \
   netplugd \
   ifplugd \
   NetworkManager \
   NetworkManagerDispatcher \
   netfs \
   netplugd \
   ncsd \
   oddjobd \
   openvpn \
   pcmcia \
   pcscd \
   portsentry \
   postfix \
   rawdevices \
   rdisc \
   rpcgssd \
   rpcidmapd \
   saslauthd \
   tcsd \
   vsftpd \
   winbind \
   wpa_supplicant \
   xfs \
   ypbind ;
   do
headerBlock "Desactivando el service: ${service}"
/sbin/chkconfig ${service} off &>/dev/null
/sbin/service ${service} stop &>/dev/null
done
/scripts/restartsrv_chkservd
}


function config_exim_log(){
	rm -rf /var/log/registro-spam.log
	touch /var/log/registro-spam.log
	chown cpaneleximfilter. /var/log/registro-spam.log
	chmod 0744 /var/log/registro-spam.log

	rm -rf /etc/antivirus2.exim
	touch /etc/antivirus2.exim
}

function installCXS(){
	cd ~
	wget https://download.configserver.com/cxsinstaller.tgz
	tar -xzf cxsinstaller.tgz
	perl cxsinstaller.pl
	rm -fv cxsinstaller.*
}

function installClamAV(){
	/scripts/ensurerpm ${verbose} gmp gmp-devel bzip2-devel libjson-c-dev libcurl-devel
	useradd clamav
	groupadd clamav
	mkdir /usr/local/share/clamav
	chown clamav:clamav /usr/local/share/clamav
	cd ~
	wget --no-check-certificate https://github.com/Cisco-Talos/clamav-devel/archive/clamav-0.101.2.tar.gz
	tar -xzf clamav-*
	rm -rf clamav-*.tar.gz
	cd clamav*
	headerBlock "Building ClamAV from source..."
	./configure --disable-zlib-vcheck ${verbose}
	make ${verbose}
	make install ${verbose}
	headerBlock "Updating configuration files for ClamAV..."
	mv -fv /usr/local/etc/freshclam.conf.sample /usr/local/etc/freshclam.conf
	mv -fv /usr/local/etc/clamd.conf.sample /usr/local/etc/clamd.conf
	sed -i -e 's/Example/#Example/g' /usr/local/etc/freshclam.conf
	sed -i -e 's/Example/#Example/g' /usr/local/etc/clamd.conf
	sed -i -e 's/#LocalSocket/LocalSocket/g' /usr/local/etc/clamd.conf
	sed -i -e 's/LocalSocketGroup/#LocalSocketGroup/g' /usr/local/etc/clamd.conf
	sed -i -e 's/clamd.socket/clamd/g' /usr/local/etc/clamd.conf
	ldconfig
	headerBlock "Updating ClamAV definition files..."
	/usr/local/bin/freshclam ${verbose}
	rm -fv /etc/init.d/clamd
	curl https://download.configserver.com/clamd.service -o /usr/lib/systemd/system/clamd.service
	systemctl daemon-reload
	systemctl enable clamd.service
	systemctl restart clamd.service
	rm -rf /etc/chkserv.d/clamav
	echo "service[clamav]=x,x,x,service clamd restart,clamd,root" >> /etc/chkserv.d/clamav
	touch /var/log/clam-update.log
	chown clamav:clamav /var/log/clam-update.log
	echo "clamav:1" >> /etc/chkserv.d/chkservd.conf
	rm -rf ~/clamav*
	headerBlock "ClamAV installed, sock will be at /tmp/clamd"
}

function installYumColors(){
	if ! grep -q 'color_list_installed_older' /etc/yum.conf ; then
		echo 'color_list_installed_older=red' >> /etc/yum.conf
	fi
	if ! grep -q 'color_list_installed_newer' /etc/yum.conf ; then
		echo 'color_list_installed_newer=yellow' >> /etc/yum.conf
	fi
	if ! grep -q 'color_list_installed_extra' /etc/yum.conf ; then
		echo 'color_list_installed_extra=red' >> /etc/yum.conf
	fi
	if ! grep -q 'color_list_available_reinstall' /etc/yum.conf ; then
		echo 'color_list_available_reinstall=green' >> /etc/yum.conf
	fi
	if ! grep -q 'color_list_available_upgrade' /etc/yum.conf ; then
		echo 'color_list_available_upgrade=blue' >> /etc/yum.conf
	fi
	if ! grep -q 'color_list_available_install' /etc/yum.conf ; then
		echo 'color_list_available_install=cyan' >> /etc/yum.conf
	fi
}

function installMailManage(){
	cd /usr/src
	rm -fv /usr/src/cmm.tgz
	wget http://download.configserver.com/cmm.tgz
	tar -xzf cmm.tgz
	cd cmm
	sh install.sh
	rm -Rfv /usr/src/cmm*
}

function installExplorer(){
	cd /usr/src
	rm -fv /usr/src/cse.tgz
	wget https://download.configserver.com/cse.tgz
	tar -xzf cse.tgz
	cd cse
	sh install.sh
	rm -Rfv /usr/src/cse*
}

function installMailQueue(){
	cd $builddir
	wget http://download.configserver.com/cmq.tgz
	tar -xzf cmq.tgz
	cd cmq
	sh install.sh
}

function installModSecurityControl(){
	cd $builddir
	wget http://download.configserver.com/cmc.tgz
	tar -xzf cmc.tgz
	cd cmc
	sh install.sh
}

function installFirewall(){
	cd $builddir
	wget https://download.configserver.com/csf.tgz
	tar -xzf csf.tgz
	cd csf
	sh install.sh
	# Statistical Graphs available from the csf UI
	yum install ${yumargs} perl-GDGraph
	# Check perl modules
	perl /usr/local/csf/bin/csftest.pl
	configureCSF
}

function installMalDetect(){
	cd $builddir
	wget https://www.rfxn.com/downloads/maldetect-current.tar.gz
	tar -xzf maldetect-*.tar.gz
	rm -rf maldetect-*.tar.gz
	cd maldetect*
	sh install.sh
}

function installMailScanner(){
	cd $builddir
	wget https://download.configserver.com/msinstall.tar.gz
	tar -xzf msinstall.tar.gz
	rm -rf msinstall.tar.gz
	cd msinstall/
	sh install.sh
	cd $builddir
	# WHM > Tweak Settings > Uncheck "SpamAssassin Spam Filter" and "SpamAssassin Spam Box"
	# WHM > Service Manager > Uncheck both boxes for spamd and click Save
	# Feature Manager > Edit the feature list "disabled" and uncheck "SpamAssassin" and "SpamAssassin Spam Box"

	sed -i -e 's/skipspamassassin=1/skipspamassassin=0/g' /var/cpanel/cpanel.config
	# Must be ran after updating tweak settings file
	/usr/local/cpanel/whostmgr/bin/whostmgr2 --updatetweaksettings > /dev/null

	echo -e "\n${WHITEBG}${BLACK}!! AVISO !! debes ir a WHM > Service Manager > Desactiva la la opcion spamd y marca Save ${NORMAL}\n";
	echo -e "\n${WHITEBG}${BLACK}!! AVISO !! ir a Feature Manager > Edit the feature list 'disabled' and uncheck 'SpamAssassin' and 'SpamAssassin Spam Box' ${NORMAL}\n";
	read -p "Press [Enter] to confirm you have completed this..."

	echo -e "\nYou can now check the files in /usr/mailscanner/etc/rules/*.rules and modify them if desired. There are instructions and examples in the README and EXAMPLES files in that directory";
	read -p "Press [Enter] to continue..."

	# MailScanner won't be scanning for much until you configure it for the domains on your server. We have another handy script that can keep your MailScanner installation in sync with your cPanel /etc/localdomains file.
	/usr/mscpanel/mscpanel.pl -i
	rm -rf msinstall/

	if stepcheck "setup daily MailScanner cronjob to keep cPanel /etc/localdomains in sync?"; then
		headerBlock "Adding MailScanner daily cron job ..."
		installMailScannerCron
	fi
}

function installMailScannerCron(){
	(crontab -l 2>/dev/null; echo "0 0 * * * /usr/mscpanel/mscpanel.pl > /dev/null 2>&1") | crontab -
}

function installSoftaculous(){
	cd $builddir
	wget -N http://files.softaculous.com/install.sh
	chmod 755 install.sh
	./install.sh
}

function installWatchMySQL(){
	cd /usr/src
	wget http://download.ndchost.com/watchmysql/latest-watchmysql
	sh latest-watchmysql
}

function installPHPiniManager(){
	cd /usr/local/cpanel/whostmgr/docroot/cgi
	wget -O addon_phpinimgr.php http://download.how2.be/whm/phpinimgr/addon_phpinimgr.php.txt
	chmod 700 addon_phpinimgr.php
}

function installCleanBackups(){
	cd /usr/src
	wget http://download.ndchost.com/cleanbackups/latest-cleanbackups
	sh latest-cleanbackups
}

function installAccountDNSCheck(){
	cd /usr/src
	wget http://download.ndchost.com/accountdnscheck/latest-accountdnscheck
	sh latest-accountdnscheck
}

function installMySQLTuner(){
	cd /usr/bin
	wget http://mysqltuner.pl/ -O mysqltuner
	chmod +x mysqltuner
}

function installModCloudFlare(){
	cd $builddir
	curl -k -L https://github.com/cloudflare/CloudFlare-CPanel/tarball/master > cloudflare.tar.gz
	tar -zxvf cloudflare.tar.gz
	cd cloudflare-*/
	./cloudflare.install.sh -k ${cloudflare_api_key} -n "${cloudflare_company_name}"
}

function addCloudFlareIPv6SubnetsToCSF(){
	# Add IPs to csf.ignore for LFD
	wget --output-document=- "https://www.cloudflare.com/ips-v6" >> /etc/csf/csf.ignore
	# Add IPs to csf.allow for Firewall
	wget --output-document=- "https://www.cloudflare.com/ips-v6" >> /etc/csf/csf.allow
}

function addCloudFlareIPv4SubnetsToCSF(){
	# Add IPs to csf.ignore for LFD
	wget --output-document=- "https://www.cloudflare.com/ips-v4" >> /etc/csf/csf.ignore
	# Add IPs to csf.allow for Firewall
	wget --output-document=- "https://www.cloudflare.com/ips-v4" >> /etc/csf/csf.allow
}

function configureMemCached(){
	if [ -f /etc/sysconfig/memcached ];then
		echo -e "\n${RED}The /etc/sysconfig/memcached file already exists, renaming to memcached.old ...\n${NORMAL}"
		mv /etc/sysconfig/memcached /etc/sysconfig/memcached.old
	fi

	echo 'PORT="22222"' >> /etc/sysconfig/memcached
	echo 'USER="memcached"' >> /etc/sysconfig/memcached
	echo 'MAXCONN="20480"' >> /etc/sysconfig/memcached
	echo 'CACHESIZE="4096"' >> /etc/sysconfig/memcached
	echo 'OPTIONS="-s /var/run/memcached/memcached.sock"' >> /etc/sysconfig/memcached
	# Add railgun user to memcached group
	usermod -a -G memcached railgun

	if [ ! -d "/var/run/memcached" ];then
		mkdir /var/run/memcached
		chown memcached.memcached /var/run/memcached
	fi

	service memcached stop
	service memcached start

	chmod 770 /var/run/memcached/memcached.sock
	echo -e "\n${NORMAL}If you want to change, review, or update memcached, use the ${YELLOW}/etc/sysconfig/memcached${NORMAL} file."
}

function installCloudFlarePackageRepo(){

	rpm --import https://pkg.cloudflare.com/pubkey.gpg
	cd $builddir
	# Get RHEL major version number
	RHEL_VERSION=$(rpm -q --qf "%{VERSION}" "$(rpm -q --whatprovides redhat-release)" | grep -Eo '^[0-9]*' );
	PACKAGE_URL="http://pkg.cloudflare.com/cloudflare-release-latest.el${RHEL_VERSION}.rpm"

	rpm -ivh $PACKAGE_URL
}

function hardenServerConfig(){

	promptForSSHPort
	promptForRootForwardEmail
	headerBlock "Securing the server with configuration tweaks, please wait..."

	# Check server startup for portreserve, use 2> /dev/null to prevent warning output (if not installed or enabled)
	service portreserve stop 2> /dev/null
	chkconfig portreserve off 2> /dev/null

	configureApache
	configureCSF
	configureSSH
	configurecPanel
	configurePureFTP
	configureTweakSettings
	configureMySQL
	configurePHP
	csf -r
	/etc/init.d/lfd restart
	/etc/init.d/httpd restart
}

function newCpanelApacheLocalConf(){
cat << 'EOF' > /var/cpanel/conf/apache/local
---
"main":
  "serversignature":
    "item":
      "serversignature": 'Off'
  "servertokens":
    "item":
      "servertokens": 'ProductOnly'
  "traceenable":
    "item":
      "traceenable": 'Off'
EOF
}

function configureApache(){

	if [ ! -f /var/cpanel/conf/apache/local ]; then
		newCpanelApacheLocalConf
		/scripts/rebuildhttpdconf
		/etc/init.d/httpd
	else
		#TODO basic sed replacement
		echo -e "cPanel Apache Local Configuration file ( /var/cpanel/conf/apache/local ) already exists, unable to update"
	fi
}

function configureCSF(){
	sed -i -e 's/RESTRICT_SYSLOG = "0"/RESTRICT_SYSLOG = "3"/g' /etc/csf/csf.conf
	sed -i -e 's/SMTP_BLOCK = "0"/SMTP_BLOCK = "1"/g' /etc/csf/csf.conf
	sed -i -e 's/LF_SCRIPT_ALERT = "0"/LF_SCRIPT_ALERT = "1"/g' /etc/csf/csf.conf
	sed -i -e 's/SYSLOG_CHECK = "0"/SYSLOG_CHECK = "1800"/g' /etc/csf/csf.conf
	sed -i -e 's/PT_ALL_USERS = "0"/PT_ALL_USERS = "1"/g' /etc/csf/csf.conf
	sed -i -e 's/TESTING = "1"/TESTING = "0"/g' /etc/csf/csf.conf
	csf -e	
}

function configureSSH(){
	sed -i -e "s/#Port 22/Port ${sshport}/g" /etc/ssh/sshd_config
	sed -i -e 's/#UseDNS yes/UseDNS no/g' /etc/ssh/sshd_config
	service sshd restart
}

function configurecPanel(){
	# Enable Shell Fork Bomb Protection
	perl -I/usr/local/cpanel -MCpanel::LoginProfile -le 'print [Cpanel::LoginProfile::install_profile('limits')]->[1];'
	# Compiler access
	chmod 750 /usr/bin/gcc
	# Enable PHP-FPM Service for cPanel
	whmapi1 configureservice service=cpanel_php_fpm enabled=1 monitored=1
	# Check Background Process Killer
	whmapi1 configurebackgroundprocesskiller processes_to_kill=BitchX processes_to_kill-0=bnc processes_to_kill-1=eggdrop processes_to_kill-2=generic-sniffers processes_to_kill-3=guardservices processes_to_kill-4=ircd processes_to_kill-5=psyBNC processes_to_kill-6=ptlink processes_to_kill-7=services
	# Root Forwarder
	if [ ! -f /root/.forward ]; then
    	echo $rootemail > /root/.forward
	fi
}

function configurePureFTP(){
	sed -i -e "s/RootPassLogins: 'yes'/RootPassLogins: 'no'/g" /var/cpanel/conf/pureftpd/main
	sed -i -e "s/AnonymousCantUpload: 'no'/AnonymousCantUpload: 'yes'/g" /var/cpanel/conf/pureftpd/main
	sed -i -e "s/NoAnonymous: 'no'/NoAnonymous: 'yes'/g" /var/cpanel/conf/pureftpd/main
	# Build configuration from cPanel FTP config
	/usr/local/cpanel/whostmgr/bin/whostmgr2 doftpconfiguration > /dev/null
}

function configureTweakSettings(){
	sed -i -e 's/skipboxtrapper=0/skipboxtrapper=1/g' /var/cpanel/cpanel.config
	sed -i -e 's/referrerblanksafety=0/referrerblanksafety=1/g' /var/cpanel/cpanel.config
	sed -i -e 's/referrersafety=0/referrersafety=1/g' /var/cpanel/cpanel.config
	sed -i -e 's/cgihidepass=0/cgihidepass=1/g' /var/cpanel/cpanel.config
	sed -i -e 's/proxysubdomains=1/proxysubdomains=0/g' /var/cpanel/cpanel.config
	sed -i -e 's/smtpmailgidonly=1/smtpmailgidonly=0/g' /var/cpanel/cpanel.config
	echo "maxemailsperhour=199" >> /var/cpanel/cpanel.config
	# Must be ran after updating tweak settings file
	/usr/local/cpanel/whostmgr/bin/whostmgr2 --updatetweaksettings > /dev/null
}

function configureMySQL(){
	if ! grep -q 'local-infile=0' /etc/yum.conf ; then
		echo 'local-infile=0' >> /etc/my.cnf
		/scripts/restartsrv_mysql
	fi
}

function configurePHP(){
	# Example ea-phpXX file location
	# /opt/cpanel/ea-php72/root/etc/php.ini
	EA_PHP_FILES=( /opt/cpanel/ea-php*/root/etc/php.ini )
	# Replace is default /usr/local/lib/php.ini files
	sed -i -e 's/enable_dl = On/enable_dl = Off/g' /usr/local/lib/php.ini
	sed -i -e 's/disable_functions =.*/disable_functions = show_source, system, shell_exec, passthru, exec, phpinfo, popen, proc_open, allow_url_fopen, ini_set/g' /usr/local/lib/php.ini
	# Replace in any /opt/cpanel/ea-phpXX/root/etc/php.ini files
	sed -i -e 's/enable_dl = On/enable_dl = Off/g' "${EA_PHP_FILES[@]}"
	sed -i -e 's/disable_functions =.*/disable_functions = show_source, system, shell_exec, passthru, exec, phpinfo, popen, proc_open, allow_url_fopen, ini_set/g' "${EA_PHP_FILES[@]}"
}

function promptForSSHPort(){
	# Configuration Prompts ( only shown when -u is NOT specified )
	if (($unattended < 1)); then
		echo -n "${MAGENTA}Enter SSH port to change from ${BLUE}${sshport}${MAGENTA}:${NORMAL} "
		read customsshport
		if [ $customsshport ]; then
			sshport=$customsshport
		fi
	fi
}

function promptForRootForwardEmail(){
	# Configuration Prompts ( only shown when -u is NOT specified )
	if (($unattended < 1)); then

		echo -n "${MAGENTA}Enter root forwarding email to change from ${BLUE}${rootemail}${MAGENTA}:${NORMAL} "
		read customrootemail
		if [ $customrootemail ]; then rootemail=$customrootemail
		fi

	fi
}

function promptForCloudFlareConfig(){
	# Configuration Prompts ( only shown when -u is NOT specified )
	if (($unattended < 1)); then

		echo -e "\n${WHITEBG}${BLACK}!! AVISO !! The mod_cloudflare module will be installed, but you need to recompile Apache with EasyApache in WHM to enable mod_cloudflare!${NORMAL}\n";
		read -p "Press [Enter] key when you are ready to continue..."

		echo -e "\nExisting value: ${BLUE}${cloudflare_api_key}${NORMAL} \n"
		echo -e "${MAGENTA}Enter your CloudFlare API Key if different from existing${MAGENTA}:${NORMAL} "
		read custom_cloudflare_api_key
		if [ $custom_cloudflare_api_key ]; then
			cloudflare_api_key=$custom_cloudflare_api_key
		fi

		echo -e "\nUsing ${BLUE}${cloudflare_api_key}${NORMAL} as CloudFlare API Key\n"

		echo -e "\nExisting value: ${BLUE}${cloudflare_company_name}${NORMAL} \n"
		echo -e "${MAGENTA}Enter your Hosting Company Name if different from existing${MAGENTA}:${NORMAL} "
		read custom_cloudflare_company_name
		if [ $custom_cloudflare_company_name ]; then
			cloudflare_company_name="${custom_cloudflare_company_name}"
		fi

		echo -e "\nUsing ${BLUE}${cloudflare_company_name}${NORMAL} as CloudFlare Company Name\n"
	fi
}

function promptForRailGunConfig(){
	# Configuration Prompts ( only shown when -u is NOT specified )
	if (($unattended < 1)); then

		server_hostname=$(hostname);
		server_ip=$(curl -4 icanhazip.com);

		echo -e "\nExisting value: ${BLUE}${railgun_token}${NORMAL} \n"
		echo -e "${MAGENTA}Enter your CloudFlare RailGun Token if different from existing (find this at https://partners.cloudflare.com)${MAGENTA}:${NORMAL} "
		read custom_railgun_token
		if [ $custom_railgun_token ]; then
			railgun_token=$custom_railgun_token
		fi

		echo -e "\nUsing ${BLUE}${railgun_token}${NORMAL} as CloudFlare RailGun Token\n"

		echo -e "\nExisting value: ${BLUE}${railgun_host}${NORMAL}"
		echo -e "\nFor reference, your hostname is ${BLUE}${server_hostname}${NORMAL}, your IP is ${BLUE}${server_ip}${NORMAL}\n"
		echo -e "${MAGENTA}Enter your CloudFlare RailGun Host if different from existing (should be servers IP or hostname)${MAGENTA}:${NORMAL} "
		read custom_railgun_host
		if [ $custom_railgun_host ]; then
			railgun_host=$custom_railgun_host
		fi

		# Set to host if nothing set
		if [ $railgun_host = 'YOUR_PUBLIC_IP_OR_HOSTNAME' ]; then
			railgun_host=$(hostname);
		fi

		echo -e "\nUsing ${BLUE}${railgun_host}${NORMAL} as CloudFlare RailGun Host\n"
	fi
}

function configureCloudFlareRailGun(){
	promptForRailGunConfig
	headerBlock "Configuring CloudFlare RailGun, please wait ..."
	sed -i -e 's/memcached.servers/#memcached.servers/g' /etc/railgun/railgun.conf
	sed -i -e 's/activation.token/#activation.token/g' /etc/railgun/railgun.conf
	sed -i -e 's/activation.railgun_host/#activation.railgun_host/g' /etc/railgun/railgun.conf
	echo "memcached.servers = /var/run/memcached/memcached.sock" >> /etc/railgun/railgun.conf
	echo "activation.token = ${railgun_token}" >> /etc/railgun/railgun.conf
	echo "activation.railgun_host = ${railgun_host}" >> /etc/railgun/railgun.conf
	headerBlock "Restarting RailGun service..."
	/etc/init.d/railgun restart
}

function configureMemCachedRailGunSockets(){
	headerBlock "Creating /etc/sysconfig/memcached configuration file, please wait ..."
	configureMemCached
	headerBlock "Restarting memcached service ..."
	service memcached restart
	headerBlock "Setting permissions on /var/run/memcached/memcached.sock to 770"
	chmod 770 /var/run/memcached/memcached.sock
	headerBlock "Adding RailGun user to memcached group"
	usermod -a -G memcached railgun
}

function installJetBackup(){
	headerBlock "Installing Jet Backup, please wait..."
	yum install http://repo.jetlicense.com/centOS/jetapps-repo-latest.rpm
	yum clean all --enablerepo=jetapps*
	yum install jetapps-cpanel --disablerepo=* --enablerepo=jetapps
	jetapps --install jetbackup stable
}

function installAfterLogicWebmailLite(){
	# Make sure 3rd party perl modules is installed
	cpan YAML::Syck
	cd $builddir;
	wget http://www.afterlogic.com/download/webmail-panel-installer.tar.gz
	tar -xzvf webmail-panel-installer.tar.gz
	cd webmail-panel*
	chmod a+x installer
	bash installer -t lite -a install

	server_hostname=$(hostname);

	echo -e "\n${WHITEBG}${BLACK}!! AVISO !! You MUST login to webmail using an active email account on your server, and then go to this URL: ${NORMAL}\n";
	echo -e "\n${WHITEBG}${BLACK} http://${server_hostname}:2095/3rdparty/afterlogic/adminpanel/index.php: ${NORMAL}\n";
	echo -e "\n${WHITEBG}${BLACK} And login with these credentials: ${NORMAL}\n";
	echo -e "\n${BLUE}Username: ${NORMAL}mailadm\n";
	echo -e "\n${BLUE}Password: ${NORMAL}12345\n";
	echo -e "\n${WHITEBG}${BLACK} !!! Once you login to admin webmail interface make SURE you change the password!!!! ${NORMAL}\n";
	echo -e "\n${WHITEBG}${BLACK} !!! If you do not ANYBODY will be able to login to the webmail admin interface!!!! ${NORMAL}\n";
	read -p "Press [Enter] key to confirm you understand and continue..."
}

function installLetsEncryptAutoSSL(){
	/scripts/install_lets_encrypt_autossl_provider
}

function installCloudFlareRailGun(){
	headerBlock "Attempting to install MemCached, please wait..."
	yum install memcached -y

	headerBlock "Adding CloudFlare RailGun package repository, please wait..."
	installCloudFlarePackageRepo

	headerBlock "Installing CloudFlare Railgun, please wait..."
	yum install railgun-stable -y

	headerBlock "Adding ... CloudFlareRemoteIPTrustedProxy 127.0.0.1 ... to apache user conf file ..."
	if grep -q "CloudFlareRemoteIPTrustedProxy" /usr/local/apache/conf/includes/post_virtualhost_global.conf ; then
		echo -e "\n${RED}CloudFlareRemoteIPTrustedProxy already found in /usr/local/apache/conf/includes/post_virtualhost_global.conf file!\n${NORMAL}"
	else
		echo "<IfModule mod_cloudflare.c>" >> /usr/local/apache/conf/includes/post_virtualhost_global.conf
		echo "CloudFlareRemoteIPHeader CF-Connecting-IP" >> /usr/local/apache/conf/includes/post_virtualhost_global.conf
		echo "CloudFlareRemoteIPTrustedProxy 127.0.0.1" >> /usr/local/apache/conf/includes/post_virtualhost_global.conf
		echo "</IfModule>" >> /usr/local/apache/conf/includes/post_virtualhost_global.conf

		headerBlock "Rebuilding apache configuration ..."
		/scripts/rebuildhttpdconf
		headerBlock "Restarting apache ..."
		/scripts/restartsrv_apache
	fi

	headerBlock "Adding memcached and rg-listener to CSF process ignore list..."
	if grep -q "exe:/usr/bin/memcached" /etc/csf/csf.pignore ; then
		echo "exe:/usr/bin/memcached" >> /etc/csf/csf.pignore
	fi
	if grep -q "exe:/usr/bin/rg-listener" /etc/csf/csf.pignore ; then
		echo "exe:/usr/bin/rg-listener" >> /etc/csf/csf.pignore
	fi
	headerBlock "Restarting ConfigServer Firewall, please wait..."
	csf -r
}
