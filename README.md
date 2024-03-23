


introduction

The Secure Password Manager (SPM) is a highly secure C++ application designed to protect and manage passwords for various accounts. In a world increasingly threatened by cyber attacks and data breaches, the importance of a reliable password storage solution is more critical than ever. SPM addresses this need by incorporating RSA encryption, one of the most trusted and powerful encryption methods available, providing unparalleled security for users' passwords.
Instruction to use the code

Main Menu: Upon starting the application, you'll be greeted by the main menu, which offers the following options:

Add Password: This option allows you to store a new password in the manager. You'll be prompted to enter the owner's name (the account or service the password is for), the password itself, and a secure number that will be needed to retrieve the password later. Use option (1)
Retrieve Password: To retrieve a password, choose this option and enter the owner's name and the secure number you provided when you added the password. If the secure number matches, the password will be decrypted and displayed. Use option (2)

Generate Random Password: Selecting this option prompts you to enter the desired length for a randomly generated password. The application will then display a password consisting of a mix of upper and lower case letters, digits, and symbols, which you can use for a new account or to update an existing password. Use option (3)

Exit: This option saves any changes made during the session (like added or modified passwords) to a file named allPasswords.txt and then closes the application. Use option(4)

Key Functions Explained
Encryption & Decryption: The application uses RSA encryption to secure your passwords. When you add a password, it's encrypted before being saved. When retrieving, the correct secure number will decrypt and reveal the original password.

Data Persistence: Passwords are stored in a text file (allPasswords.txt). Each time you start the application, it loads existing passwords from this file. When exiting, any new or modified entries are saved back to the file, ensuring that your passwords are not lost between sessions.
Security Measures: Do not share the allPasswords.txt file or your secure numbers with anyone. The security of your passwords relies on keeping these elements confidential.





