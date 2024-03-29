#!/bin/bash
version="1.7.0";
cpSetup_banner() {
	echo -n "${GREEN}"
	cat <<"EOT"
  _________.__                   __          
 /   _____/|  |__   ____   _____/  |______   
 \_____  \ |  |  \ /  _ \ /  _ \   __\__  \  
 /        \|   Y  (  <_> |  <_> )  |  / __ \_
/_______  /|___|  /\____/ \____/|__| (____  /
        \/      \/                        \/ 
EOT
echo -e "${BLUE}                       Version ${version}${YELLOW}"
	cat <<"EOT"
   ____                               __            _             
  / __ \ _ __ ___   __ _ _ __   ___  / _| ___  _ __(_) ___  _ __  
 / / _` | '_ ` _ \ / _` | '_ \ / _ \| |_ / _ \| '__| |/ _ \| '_ \ 
| | (_| | | | | | | (_| | | | | (_) |  _| (_) | |  | | (_) | | | |
 \ \__,_|_| |_| |_|\__,_|_| |_|\___/|_|  \___/|_|  |_|\___/|_| |_|
  \____/                                                          
EOT
echo -n "${NORMAL}"
}
#                     Shoota cpanel Script
# ------------------------------------------------------------------------------
# @usage ./shoota [(-h|--help)] [(-v|--verbose)] [(-V|--version)] [(-u|--unattended)]
# ------------------------------------------------------------------------------
# @copyright Copyright (C) 2019 itfinden spa
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
# ------------------------------------------------------------------------------

# Uncomment out the code below to make the script break on error
# set -e
#
# Functions and Definitions
#
# Define help function

source ./app/shoota_help.inc
source ./shoota_config.conf


# Declare vars. Flags initalizing to 0.
verbose="--quiet";
yumargs="";
unattended=0;
builddir=~/shoota_build/
functions=0;

# Debugging on OSX (due to getopt issues), so i define brew location for getopt in env variable
if [[ -z "${SMYLES_GETOPT}" ]]; then
	# ENV variable not set, so use default getopt
	GETOPT_CMD="getopt"
else
	GETOPT_CMD="${SMYLES_GETOPT}"
fi

# Execute getopt
ARGS=$("$GETOPT_CMD" -o "hvVur:R" -l "help,verbose,version,unattended,run:,functions" -n "shoota" -- "$@");

#Bad arguments
if [ $? -ne 0 ];
then
    help;
fi
eval set -- "$ARGS";

while true; do
    case "$1" in
        -h|--help)
            shift;
            help;
            ;;
        -v|--verbose)
            shift;
                    verbose="";
            ;;
        -V|--version)
            shift;
                    echo "$version";
                    exit 1;
            ;;
        -u|--unattended)
            shift;
                    unattended="1";
                    yumargs="-y";
            ;;
        -r|--run)
            shift;
                    if [ -n "$1" ];
                    then
                        runcalled="1";
                        run="$1";
                        shift;
                    fi
            ;;
        -R|--functions)
            shift;
            	functions=1;
            ;;

        --)
            shift;
            break;
            ;;
    esac
done

CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

source ./app/shoota_global.inc
source ./app/shoota_func.inc

cpanel_installed=$(/usr/local/cpanel/cpanel -V 2>/dev/null)

clear
cpSetup_banner
echo -e "\n";
if (($functions > 0 )); then
	echo -e "${RED}Aquí hay una lista de las funciones disponibles para verlos se usa el comando -r o --run:${NORMAL}"
	echo -e "\n";
	compgen -A function | egrep -vw 'givemeayes|help|headerBlock|lineBreak|stepcheck|promptForSSHPort|promptForRootForwardEmail|cpSetup_banner';
	echo -e "\n";
	exit;
fi

if [ -z "$cpanel_installed" ]; then
	echo -e "${WHITEBG}${RED}${BRIGHT}${BLINK}AVISO!${NORMAL}${WHITEBG}${BLACK}Parece que cPanel no está instalado en este servidor!${NORMAL}"
	if givemeayes "${RED}¿Le gustaría instalar cPanel antes de ejecutar este script??${NORMAL}"; then
		headerBlock "No hay problema, primero instalemos cPanel ... esto podría tardar un minuto ... o dos ... o treinta ... por favor, espere ..."
		echo -e "\n";
		read -p "Presione la tecla [Enter] cuando esté listo ..."
		cd /home && curl -o latest -L http://httpupdate.cpanel.net/latest && sh latest
	else
		if ! givemeayes "${RED}De acuerdo, no hay problema, ¿desea continuar con este script (sin instalar cPanel)??${NORMAL}"; then
			echo -e "\n${RED}Script eliminado, nada ha sido cambiado o instalado.\n${NORMAL}"
			exit;
		fi
	fi
fi

echo -e "${WHITEBG}${RED}${BRIGHT}${BLINK}Aviso!${NORMAL}${WHITEBG}${BLACK} Un par de cosas que debes saber sobre este script:${NORMAL}"
echo -e "* Debes Tener habilitado ${YELLOW}ioncube${NORMAL} en ${YELLOW}WHM${NORMAL} ${BLUE}Tweak Settings${NORMAL} > ${MAGENTA}cPanel PHP Loader${NORMAL} para instalar Softaculous (opcional)"
echo -e "* Debes pasar por la configuración inicial en ${YELLOW}WHM${NORMAL}, seleccionando el tipo de servidor dns y ftp (cuando inicias sesión por primera vez en WHM) antes de ejecutar este script."
echo -e "${BLUE}Te gusto este Script?  trabajemos por un cpanel mas seguro en https://github.com/itfinden/shoota ... !${NORMAL}"
echo -e "\n";

if (($unattended > 0)); then
	echo -e "${YELLOW}!!! WARNING: Unattended mode ENABLED, MAKE SURE YOU SET ALL CONFIG VALUES IN THIS SCRIPT !! YOU HAVE BEEN WARNED !!${NORMAL}"
fi

if [ $run ]; then
	echo -e "${YELLOW}RUN command specified, only the${RED} $run ${YELLOW}function will be executed. ${NORMAL}"
fi

echo -e "\n";

if ! givemeayes "${RED}Empezamos con la Instalacion?${NORMAL}"; then
	echo -e "\n${RED}Script eliminado, nada ha sido cambiado o instalado.\n${NORMAL}"
	exit;
fi

if [ -d "$builddir" ]; then
	rm -rf $builddir
fi

mkdir $builddir

if [ $run ]; then
	${run}
	exit;
fi

if stepcheck "Todas las actualizaciones del Servidor (Recomendado)"; then
	headerBlock "Actualizando los Paquetes por favor espere..."
	yum clean all ${verbose}
	yum update ${yumargs} ${verbose}
fi

if stepcheck "Desabilitador Servicios Inutiles"; then
	headerBlock "Desabilitar Todos los Servicios Inutiles e Inseguros"
	disable_service
fi

if stepcheck "Compilar al EasyApache"; then
	headerBlock "Agrega Configuraciones a EasyApache"
	Compilar_EasyApache
fi


if stepcheck "Mejoras al PHP"; then
	headerBlock "Mejoras a todos los PHP"
	Ajustes_php
fi

if stepcheck "Rectificar Mejoras al PHP"; then
	headerBlock "Mejoras a todos los PHP Rectificada"
	Rectifica_php
fi

if stepcheck "Mejoras al TweakSettings"; then
	headerBlock "Agrega Configuraciones a TweakSettings"
	Best_TweakSettings
fi

if stepcheck "Mejoras al Kernel"; then
	headerBlock "Agrega Configuraciones a Kernel"
	hardering_kernel
fi

if stepcheck "Mejoras a Mysql"; then
	headerBlock "Agrega Configuraciones a MySQL"
	mysql_best_config
fi



if stepcheck "Configurar Exim"; then
	headerBlock "Agregando Configuraciones a Exim"
	config_exim_log
fi

if stepcheck "Yum colors"; then
	headerBlock "Adding yum colors if does not exist..."
	installYumColors
fi

if stepcheck "Comodo (Recomendado)"; then
	headerBlock "Instalando : Comodo, Por favor espere..."
	installComodo
fi

if stepcheck "ConfigServer MailManage (Recomendado)"; then
	headerBlock "Instalando : ConfigServer MailManage, Por favor espere..."
	installMailManage
fi

if stepcheck "ConfigServer MailQueue"; then
	headerBlock "Instalando : ConfigServer MailQueue, Por favor espere..."
	installMailQueue
fi

if stepcheck "ConfigServer Firewall (Recomendado)"; then
	headerBlock "Instalando : ConfigServer Firewall, Por favor espere..."
	installFirewall
fi

if stepcheck "ConfigServer ModSecurity Control (WHM lo tiene incorporado)"; then
	headerBlock "Instalando : ConfigServer ModSecurity Control, Por favor espere..."
	installModSecurityControl
fi

if stepcheck "ConfigServer Explorer"; then
	headerBlock "Instalando : ConfigServer Explorer, Por favor espere..."
	installExplorer
fi

if stepcheck "R-fx Malware Detect"; then
	headerBlock "Instalando : R-fx Malware Detect, Por favor espere..."
	installMalDetect
fi

if stepcheck "ConfigServer Exploit Scanner (require licencia)"; then
	headerBlock "Instalando : ConfigServer Exploit Scanner, Por favor espere..."
	installCXS
fi

echo -e "\n";
echo -n "${YELLOW}!! AVISO !!${RED}( DEBES hacer esto AHORA ): ${NORMAL}Debe tener ioncube habilitado en WHM en Configuración de Tweak> cPanel PHP Loader o Softaculous no se instalará"
echo -e "\n";
if stepcheck "Softaculous"; then
	headerBlock "Instalando : Softaculous, Por favor espere..."
	installSoftaculous
fi

if stepcheck "Account DNS Check"; then
	headerBlock "Instalando : Account DNS Check, Por favor espere..."
	installAccountDNSCheck
fi

if stepcheck "WatchMySQL (Deprecado)"; then
	headerBlock "Instalando : WatchMySQL, Por favor espere..."
	installWatchMySQL

	#watchmysql
	#wget http://download.ndchost.com/watchmysql/latest-watchmysql
	#sh latest-watchmysql
	#/var/cpanel/addons/watchmysql/bin/uninstall
    #rm -f latest-watchmysql
fi

if stepcheck "MySQL Tuner"; then
	headerBlock "Instalando : MySQL Tuner, Por favor espere..."
	installMySQLTuner
fi

if stepcheck "harden server configuration"; then
	hardenServerConfig
fi

if stepcheck "ClamAV desde los originales"; then
	headerBlock "Instalando : ClamAV from source, Por favor espere..."
	installClamAV
fi

if stepcheck "CloudFlare mod_cloudflare"; then
	promptForCloudFlareConfig
	headerBlock "Descargando e Instalando : mod_cloudflare, Por favor espere..."
	installModCloudFlare
fi

if stepcheck "agregue las subredes IPv4 e IPv6 de CloudFlare a la lista de permitidos del firewall ConfigServer"; then
	headerBlock "agregando sub redes IPv4 a las listas permitidas de CSF, Por favor espere..."
	addCloudFlareIPv4SubnetsToCSF
	headerBlock "Agregando sub redes IPv6 a las listas permitidas de CSF, Por favor espere..."
	addCloudFlareIPv4SubnetsToCSF
	headerBlock "Re Iniciando ConfigServer Firewall, Por favor espere..."
	csf -r
fi

if stepcheck "CloudFlare RailGun (Incluido memcached)"; then
	installCloudFlareRailGun
fi

if stepcheck "configurar memcached para RailGun usando sockets"; then
	configureMemCachedRailGunSockets
fi

if stepcheck "configure CloudFlare RailGun"; then
	configureCloudFlareRailGun
fi

if stepcheck "AfterLogic WebMail Lite"; then
	installAfterLogicWebmailLite
fi

if stepcheck "Lets Encrypt for AutoSSL"; then
	installLetsEncryptAutoSSL
fi

headerBlock "Limpiando archivos de compilación, Por favor espere..."
cd ~
rm -rf $builddir
echo -e "\n${CYAN}Script Complete! Excelente!\n${NORMAL}"
echo -e "\n${WHITEBG}${RED}!!! Si instaló mod_cloudflare, NO TE OLVIDES de iniciar sesión en WHM y recompilar Apache con mod_cloudflare (usando EasyApache) !!! \n${NORMAL}"
