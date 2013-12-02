# OS Help

After running `drush build_docs`, the OS Help module's /help/ directory should
contain all the advanced help files provided by OpenScholar modules. Individual
OpenScholar modules may provide three types of files:

* Advanced Help fragments in files named like `mymodule.os_help.ini.` (required)
* HTML files that share a base name with an ini file. (optional)
* Images in an image directory (optional). Note: please namespace your images.

The conventional location is in a the help directory:

  ../mymodule/
    - mymodule.info
    - mymodule.module
    - help/
      - mymodule.os_help.ini
      - mymodule.html
      - images/
        - mymodule_foobar.png

In this example module directory structure, mymodule.os_help.ini is appended to
os_help/help/os_help.help.ini, mymodule.html is copied to os_help/help/ one
image (mymodule_foobar.png) is found and added to OS Help's /help/images/
directory.

Important: As with AH, you should link to images like:

  src="path:/images/IMAGE_NAME.EXT"

And be sure to use double quotes so that 'path' gets replaced.