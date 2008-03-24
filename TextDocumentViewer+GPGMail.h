/* TextDocumentViewer+GPGMail.h created by stephane on Tue 04-Jul-2000 */

/*
 *	Copyright Stephane Corthesy (stephane@sente.ch), 2000-2005
 *	(see LICENSE.txt file for license information)
 */

#import <TextDocumentViewer.h>


@class GPGMessageViewerAccessoryViewOwner;


@interface TextDocumentViewer(GPGMail)

- (Message *) gpgMessage;

- (void) gpgShowPGPSignatureBanner;
- (void) gpgShowPGPEncryptedBanner;
- (void) gpgHideBanner;

- (BOOL) gpgValidateAction:(SEL)anAction;

// Actions connected to menus
- (IBAction) gpgDecrypt:(id)sender;
- (IBAction) gpgAuthenticate:(id)sender;

- (void) gpgForwardAction:(SEL)action from:(id)sender;

- (GPGMessageViewerAccessoryViewOwner *) gpgMessageViewerAccessoryViewOwner;

@end
