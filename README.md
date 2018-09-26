# base_tcp
# usage:
1. Start server: ./server
2. Connect to server: sftp -S ./client <ip>
"sftp-classic" is unchanged sftp executable
"sftp" has modifications - it runs executable under "-S" flag with <ip> argument only
