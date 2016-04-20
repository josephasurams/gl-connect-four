# Introduction #

We'll use Subversion for the project so that we can all work off of the same copy of the code. It will allow us to do the project without having to meet up somewhere.

If you've never used Subversion before, you should read the first paragraph on its Wikipedia page ([Subversion](http://en.wikipedia.org/wiki/Subversion_%28software%29)) to see what it is and why it's used.


# Setup #
  1. To use Subversion through Visual Studio 2008, you have to install a plugin. Download it  here and install it. http://ankhsvn.net/downloads/2.1/
  1. In this googlecode project, go to the 'Source' tab. (make sure you're already logged in with your gmail account!)
  1. Click the link that says "google.com password"
  1. Copy the bold generated password, you'll need it in a minute.
  1. Start Visual Studio, go to File > Subversion > Open From Subversion
  1. In the file browser window that pops up, there is a box at the top that lets you enter a URL. In this box, type: https://gl-connect-four.googlecode.com/svn/trunk/
  1. A login box pops up, enter your gmail login name (without the @gmail.com part) and the password you just copied down.
  1. Browse down to the .sln file and open it. A box pops up with options for importing the project. Just leave everything default and hit okay.

# Usage #
After installing the plugin you should have a new window at the bottom of Visual Studio. It has two buttons you need to be concerned about: **Commit** and **Update**

Update updates your local copy of the code to the copy of the code currently on the server. This means you'll get any changes anyone else in the group has made to the project.

A Commit sends your changes to the server, replacing the server's copy.

You can revert to any previous copy of the source code, so don't worry about messing up your copy of the code. Just don't mess up the repository!