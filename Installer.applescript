(*
 *	Mail bundle installer
 *
 *  Copyright (c) 2000-2008, St�phane Corth�sy <stephane at sente.ch>
 *  All rights reserved.
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *      * Neither the name of St�phane Corth�sy nor the names of GPGMail
 *        contributors may be used to endorse or promote products
 *        derived from this software without specific prior written permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY ST�PHANE CORTH�SY AND CONTRIBUTORS ``AS IS'' AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL ST�PHANE CORTH�SY AND CONTRIBUTORS BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *)
(*
 * Welcome to GPGMail Installer
 *
 * This application will install GPGMail in the folder 
 * Library/Mail/Bundles of your home folder, 
 * and remove existing copies of GPGMail.
 *)
(*
WARNING: does not support a space in mounted disk image path!
Due to the inability of AppleScript to find a "FileVaulted" home directory
or even a networked one, we need to use shell to do the work.
And even worse, we need to use CpMac to copy files, because cp doesn't
understand resource forks, nor meta-data.
CpMac has to be bundled in disk image
*)

copy my (system attribute "sysv") to system_string

-- 4160 = 0x1040
if not (system_string < 4160) then
	display dialog �
		"This bundle is not compatible with your system. You need to download the version for 10.3." buttons {"Quit"} with icon caution
else
	local emailAddress
	local packageName
	set emailAddress to "gpgmail@sente.ch"
	set packageName to "GPGMail.mailbundle"
	try
		local destinationFolder
		local homeFolder
		set homeFolder to (((system attribute "HOME") as string) & "/")
		set destinationFolder to homeFolder & "Library/Mail/Bundles/"
		tell application "Finder"
			local sourceFolder
			local aFolder
			local myPlist
			local myCommand
			set sourceFolder to container of (path to me)
			
			-- First we check wether Mail is still running
			if application process "Mail" exists then
				tell me
					display dialog �
						"You need to quit Mail first." buttons {"Cancel", "Quit Mail"} �
						default button 2 �
						with icon caution
				end tell
				if the button returned of the result is "Cancel" then tell me to quit
				tell application "Mail" to quit
			end if
			
			-- Then we create the folder hierarchy ~/Library/Mail/Bundles
			set myCommand to "mkdir -p '" & destinationFolder & "'"
			tell current application to do shell script myCommand
			
			if (system_string � 4161) then
				set BundleCompatibilityVersion to "2"
			else
				set BundleCompatibilityVersion to "1"
			end if
			-- Now we enable bundles for Mail
			-- PROBLEM: command 'defaults' is available only if user installed BSD package!
			set myPlist to (homeFolder & "Library/Preferences/com.apple.mail.plist")
			set myCommand to "'" & POSIX path of ((item "plistutil" of sourceFolder) as string) & "'" & " -write '" & myPlist & "' EnableBundles 1"
			tell current application to do shell script myCommand
			set myCommand to "'" & POSIX path of ((item "plistutil" of sourceFolder) as string) & "'" & " -write '" & myPlist & "' BundleCompatibilityVersion " & BundleCompatibilityVersion
			tell current application to do shell script myCommand
			
			-- We move the old GPGMail.mailbundle to the trash
			set myCommand to "test ! -e '" & destinationFolder & packageName & "' || test ! -e '" & homeFolder & ".Trash" & "' || mv '" & destinationFolder & packageName & "' '" & homeFolder & ".Trash/" & packageName & "-" & (current date) & "'"
			tell current application to do shell script myCommand
			-- and copy the new one to the right location
			set myCommand to "'" & POSIX path of ((item "CpMac" of sourceFolder) as string) & "' -r '" & POSIX path of ((item packageName of sourceFolder) as string) & "' '" & destinationFolder & "'"
			tell current application to do shell script myCommand
			
			-- We also remove bundles in other locations (/Library/Mail/Bundles)
			set aFolder to path to "dlib" from local domain
			if item "Mail" of aFolder exists then
				set aFolder to item "Mail" of aFolder
				if item "Bundles" of aFolder exists then
					set aFolder to item "Bundles" of aFolder
					if item packageName of aFolder exists then
						move item packageName of aFolder to the trash
						--					delete item packageName of aFolder
					end if
				end if
			end if
			
			-- If there is an executable named post-install, then we execute it
			if (item "post-install" of sourceFolder exists) then
				set myCommand to "'" & POSIX path of ((item "post-install" of sourceFolder) as string) & "'"
				tell current application to do shell script myCommand
			end if
			
		end tell
		display dialog (packageName & " has been successfully installed in " & (destinationFolder as string) & ".") �
			buttons {"Quit", "Launch Mail"} default button 2
		if not (the button returned of the result is "Quit") then
			tell application "Mail" to run
		end if
	on error errorText number errorNumber
		if not (errorNumber is equal to -128) then -- User cancelled
			display dialog �
				"Problem during the install of " & packageName & ": " & errorText & return & return & �
				"Proceed to manual install and send a bug report to " & emailAddress & �
				"." buttons {"Compose bug report", "Quit"} default button 2 with icon 2
			if not (the button returned of the result is "Quit") then
				tell application "Mail" to mailto "mailto:" & emailAddress
			end if
		end if
	end try
end if
