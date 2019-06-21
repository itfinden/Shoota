function help(){
    echo "cpsetup - sMyles cPanel setup script v${version}";
    echo "Usage example:";
    echo "cpsetup [(-h|--help)] [(-v|--verbose)] [(-V|--version)] [(-u|--unattended)] [(-r|--run) value] [(-R|--functions)]";
    echo "Options:";
    echo "-h or --help: Displays this information.";
    echo "-v or --verbose: Verbose mode on.";
    echo "-V or --version: Displays the current version number.";
    echo "-u or --unattended: Unattended installation ( bypasses all prompts ).";
    echo "-r or --run: Run a specific function.";
    echo "-R or --functions: Show available functions to use with -r or --run command.";
    exit 1;
}
