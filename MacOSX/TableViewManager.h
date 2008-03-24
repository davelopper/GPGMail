#import <Cocoa/Cocoa.h>

#ifdef LEOPARD

@class ASExtendedTableView;
@class MessageMall;
@class Message;
@class VisibleStateObject;
@class MessageThread;
@class BytesFormatter;

@protocol MVSelectionOwner
- (id)selection;
- (void)selectMessages:(id)fp8;
- (id)currentDisplayedMessage;
- (id)messageStore;
- (BOOL)transferSelectionToMailbox:(id)fp8 deleteOriginals:(BOOL)fp12;
@end

@protocol MessageBrowserController <NSObject, MVSelectionOwner>
- (id)messageBrowserView;
- (BOOL)isSelectionVisible;
- (void)showSelectionAndCenter:(BOOL)fp8;
- (void)updateTextViewerToSelection;
- (id)messagesToTransfer;
- (void)willTransferMessages:(id)fp8 toMailbox:(id)fp12 deleteOriginals:(BOOL)fp16;
- (void)transfer:(id)fp8 didCompleteWithError:(id)fp12;
- (id)messageToSelectIfEntireSelectionRemoved;
- (void)selectNextMessage:(BOOL)fp8;
- (void)selectPreviousMessage:(BOOL)fp8;
- (void)selectNextMessageMovingDownward:(BOOL)fp8;
- (void)selectNextMessageMovingUpward:(BOOL)fp8;
- (BOOL)includeDeleted;
- (void)setIncludeDeleted:(BOOL)fp8;
- (BOOL)shouldDeleteGivenCurrentState;
- (void)deleteSelectionAllowingMoveToTrash:(BOOL)fp8;
- (void)deleteMessages:(id)fp8 allowMoveToTrash:(BOOL)fp12 allowUndo:(BOOL)fp16;
- (void)undeleteMessagesAllowingUndo:(BOOL)fp8;
- (void)undeleteMessages:(id)fp8 allowUndo:(BOOL)fp12;
@end

@interface TableViewManager : NSObject <MessageBrowserController>
{
    ASExtendedTableView *_tableView;
    MessageMall *_messageMall;
    id _delegate;
    NSArray *_tableColumns;
    NSFont *_font;
    NSFont *_boldFont;
    NSFont *_noteFont;
    NSMutableArray *_selection;
    NSArray *_selectionExcludingThreads;
    BOOL _suspendChangesToScrollingAndSelection;
    Message *_currentDisplayedMessage;
    NSMapTable *_storeStateTable;
    NSMutableArray *_draggedMessages;
    NSMutableAttributedString *_truncatedString;
    NSMutableDictionary *_truncatedStringAttributes;
    NSMutableDictionary *_truncatedParagraphStyle;
    NSString *_availableStatusImageName;
    int leftmostTextColumn;
    struct {
        unsigned int includeDeleted:1;
        unsigned int isFocused:1;
        unsigned int sortColumnOrderAscending:1;
        unsigned int isShowingSearchResults:1;
        unsigned int sortColumnOrder:8;
        unsigned int hasScrolledSinceMailboxChange:1;
        unsigned int userChangedSelectionSinceMailboxChange:1;
        unsigned int threadOpeningIsInProgress:1;
        unsigned int threadClosingIsInProgress:1;
        unsigned int doubleClickThreadOpeningIsInProgress:1;
        unsigned int animatingThreadOpening:1;
        unsigned int animatingThreadClosing:1;
        unsigned int animateInSlowMotion:1;
        unsigned int dontUpdateTrackingRects:1;
        unsigned int dontReadWriteStoreSpecificDefaultsToMailbox:1;
        unsigned int useBoldFontForUnreadMessages:1;
        unsigned int clearingSearch:1;
        unsigned int changingSelection:1;
        unsigned int selectionShouldNotChange:1;
        unsigned int searchSortColumnOrder:8;
        unsigned int searchSortColumnOrderAscending:1;
    } _flags;
    NSDictionary *_messageIDsToSelectWhenOpened;
    NSArray *_threadIDsToOpenWhenOpened;
    int colorHighlightLeftEdge;
    int colorHighlightWidth;
    int _windowWidthBeforeSearch;
    VisibleStateObject *_visibleStateBeforeSearch;
    NSMutableSet *_messagesInSelectedThread;
    MessageThread *threadBeingClosed;
    MessageThread *threadBeingOpened;
    struct __CFDictionary *_rowDrawingCache;
    NSMutableSet *_mouseTrackers;
    struct _NSPoint _lastMouseDownInUnreadColumnPoint;
    int _lastMouseDownInUnreadColumnEventNumber;
    struct _NSPoint _currentMouseLocationInWindow;
    float _amountToScrollDownAfterClosingThread;
    int _numberOfSelectedRowsBeforeTogglingThread;
    int _selectedRowBeforeTogglingThread;
    BOOL _unreadColumnResizableAfterResizingColumnsToFit;
    BytesFormatter *_bytesFormatter;
}

+ (void)initialize;
- (void)awakeFromNib;
- (id)tableViewGetDefaultMenu:(id)fp8;
- (id)_bytesFormatter;
- (void)_setBytesFormatter:(id)fp8;
- (void)tableViewScrolled:(id)fp8;
- (void)_setupColumnHeaderIcon:(id)fp8 inColumnWithIdentifier:(id)fp12 accessibilityTitle:(id)fp16 alignment:(unsigned int)fp20;
- (void)_setupTableColumnWidths;
- (void)_configureColumnForEndTruncation:(id)fp8;
- (void)_configureColumnForImageCell:(id)fp8 alignment:(unsigned int)fp12;
- (void)_configureColumnForRolloverCell:(id)fp8 alignment:(unsigned int)fp12 action:(SEL)fp16;
- (void)showFollowupsToMessage:(id)fp8;
- (void)showFollowupsToMessageAtRow:(int)fp8;
- (void)_setupColumnsForTableView;
- (void)dealloc;
- (void)windowWillClose:(id)fp8;
- (id)delegate;
- (void)setDelegate:(id)fp8;
- (void)setMessageMall:(id)fp8;
- (void)messagesUpdated:(id)fp8;
- (void)readDefaultsFromDictionary:(id)fp8;
- (void)writeDefaultsToDictionary:(id)fp8;
- (void)setDontReadWriteStoreSpecificDefaultsToMailbox:(BOOL)fp8;
- (void)writeStoreSpecificDefaultsToMailboxUid:(id)fp8;
- (void)readStoreSpecificDefaultsFromMailboxUid:(id)fp8;
- (void)readStoreSpecificDefaultsFromDictionary:(id)fp8;
- (BOOL)canSelectNextMessage;
- (BOOL)canSelectPreviousMessage;
- (void)rulePreferencesChanged:(id)fp8;
- (void)viewerPreferencesChanged:(id)fp8;
- (BOOL)threadHasSelectedMessages:(id)fp8;
- (void)presencePreferenceChanged:(id)fp8;
- (void)threadColorPreferenceChanged:(id)fp8;
- (void)presenceImageChanged:(id)fp8;
- (void)presenceChanged:(id)fp8;
- (void)_updateTableHeaderToMatchCurrentSort;
- (void)tableView:(id)fp8 didClickTableColumn:(id)fp12;
- (id)_columnWithIdentifierTag:(int)fp8;
- (id)_unreadColumn;
- (BOOL)isColumnVisible:(int)fp8;
- (void)setColumn:(int)fp8 toVisible:(BOOL)fp12;
- (void)_setColumn:(int)fp8 toVisible:(BOOL)fp12;
- (int)tableViewNumberOfColumnsToPinToLefthandSide:(id)fp8;
- (void)selectAllMessagesAndMakeFirstResponder;
- (void)makeMessageListFirstResponder;
- (void)updateTableViewRowHeight;
- (void)setFont:(id)fp8;
- (void)setNoteFont:(id)fp8;
- (BOOL)isInThreadedMode;
- (void)toggleThreadedMode;
- (void)threadedModeDidChange:(id)fp8;
- (void)_invalidateSelectionExcludingThreads;
- (BOOL)openThreadAtIndex:(int)fp8 andSelectMessage:(id)fp12 animate:(BOOL)fp16;
- (BOOL)closeThreadAtIndex:(int)fp8 focusRow:(int)fp12 animate:(BOOL)fp16;
- (void)openAllThreads;
- (void)closeAllThreads;
- (void)toggleThread:(id)fp8;
- (void)toggleThread:(id)fp8 ignoreModifierKeys:(BOOL)fp12;
- (int)_indexOfMessageNearest:(int)fp8 numberOfRows:(int)fp12 threaded:(BOOL)fp16 downward:(BOOL)fp20;
- (BOOL)canSelectPreviousThreadedMessage;
- (BOOL)canSelectNextThreadedMessage;
- (BOOL)canSelectParentOfMessage;
- (BOOL)canSelectFirstReplyToMessage;
- (BOOL)canSelectNextReplyToParent;
- (BOOL)selectionIsExactlyOneOpenThread;
- (void)selectNextMessageMovingDownward:(BOOL)fp8;
- (void)selectNextMessageMovingUpward:(BOOL)fp8;
- (BOOL)stepIntoSelectedThread;
- (BOOL)stepOutOfSelectedThread;
- (BOOL)openSelectedThread;
- (void)selectNextMessage:(BOOL)fp8;
- (void)selectPreviousMessage:(BOOL)fp8;
- (void)selectParentOfMessage;
- (void)selectFirstReplyToMessage;
- (void)selectPeer:(BOOL)fp8;
- (void)selectNextReplyToParent;
- (void)selectPreviousReplyToParent;
- (void)showSelectionAndCenter:(BOOL)fp8;
- (BOOL)isSelectionVisible;
- (void)scrollRowToVisible:(int)fp8 position:(int)fp12;
- (int)tableView:(id)fp8 shouldScrollRowToVisible:(int)fp12;
- (BOOL)_isMessageInSelectedThread:(id)fp8;
- (void)_setNeedsDisplayForMessagesInSet:(id)fp8 highlightOnly:(BOOL)fp12;
- (void)_setNeedsDisplayThreadColumnForMessagesInSet:(id)fp8;
- (void)_updateSelectedThreadList;
- (id)selectedThread;
- (void)_reallyUpdateTextViewerToSelection;
- (void)updateTextViewerToSelection;
- (BOOL)tableView:(id)fp8 shouldSelectRow:(int)fp12 byExtendingSelection:(BOOL)fp16;
- (void)selectionIsChanging:(id)fp8;
- (void)_selectOrDeselectMembersOfThread:(id)fp8 atIndex:(int)fp12 select:(BOOL)fp16;
- (void)selectionChanged:(id)fp8;
- (void)datesNeedRedisplay;
- (int)numberOfRowsInTableView:(id)fp8;
- (id)_attributesForTruncatedParagraphStyle;
- (id)_colorForMessage:(id)fp8 inRow:(int)fp12;
- (id)_truncatedAttributedStringForString:(id)fp8 message:(id)fp12 row:(int)fp16 shouldIndent:(BOOL)fp20;
- (id)_attributedUpdatedStringForRSSMessage:(id)fp8 row:(int)fp12;
- (id)tableView:(id)fp8 typeSelectStringForTableColumn:(id)fp12 row:(int)fp16;
- (BOOL)tableView:(id)fp8 shouldTypeSelectForEvent:(id)fp12 withCurrentSearchString:(id)fp16;
- (id)tableView:(id)fp8 objectValueForTableColumn:(id)fp12 row:(int)fp16;
- (void)_updateColorHighlightEdges;
- (void)tableView:(id)fp8 didDragTableColumn:(id)fp12;
- (void)tableViewDidEndLiveResize:(id)fp8;
- (void)tableViewColumnDidMove:(id)fp8;
- (void)tableViewColumnDidResize:(id)fp8;
- (void)tableView:(id)fp8 willDisplayCell:(id)fp12 forTableColumn:(id)fp16 row:(int)fp20;
- (id)tableViewHighlightColor:(id)fp8;
- (int)tableView:(id)fp8 highlightStyleForRow:(int)fp12 inRect:(struct _NSRect *)fp16 color:(id *)fp20;
- (void)doubleClickedMessage:(id)fp8;
- (void)deleteKeyPressed;
- (void)deleteSelectionAllowingMoveToTrash:(BOOL)fp8;
- (id)selectionIncludingThreads:(BOOL)fp8;
- (id)selection;
- (void)_selectMessages:(id)fp8 scrollIfNeeded:(BOOL)fp12;
- (void)selectMessages:(id)fp8;
- (id)currentDisplayedMessage;
- (void)setCurrentDisplayedMessage:(id)fp8;
- (id)messageStore;
- (id)orderOfFromSubjectDateColumns;
- (id)tableView;
- (BOOL)tableView:(id)fp8 doCommandBySelector:(SEL)fp12;
- (id)_undoActionNameForMessageCount:(unsigned int)fp8;
- (void)selectMessagesForUndo:(id)fp8;
- (void)_undeleteMessages:(id)fp8 allowUndo:(BOOL)fp12 unreadMessages:(id)fp16;
- (void)undeleteMessages:(id)fp8 allowUndo:(BOOL)fp12;
- (void)_redeleteMessages:(id)fp8 messagesToSelect:(id)fp12;
- (void)deleteMessages:(id)fp8 allowMoveToTrash:(BOOL)fp12 allowUndo:(BOOL)fp16;
- (void)undeleteMessagesAllowingUndo:(BOOL)fp8;
- (BOOL)shouldDeleteGivenCurrentState;
- (void)tableViewDraggedImage:(id)fp8 movedTo:(struct _NSPoint)fp12;
- (unsigned int)tableView:(id)fp8 draggingSourceOperationMaskForLocal:(BOOL)fp12;
- (id)messagesToTransfer;
- (void)willTransferMessages:(id)fp8 toMailbox:(id)fp12 deleteOriginals:(BOOL)fp16;
- (void)transfer:(id)fp8 didCompleteWithError:(id)fp12;
- (BOOL)transferSelectionToMailbox:(id)fp8 deleteOriginals:(BOOL)fp12;
- (void)tableViewDragWillEnd:(id)fp8 operation:(unsigned int)fp12;
- (BOOL)tableView:(id)fp8 writeRowsWithIndexes:(id)fp12 toPasteboard:(id)fp16;
- (void)pasteboard:(id)fp8 provideDataForType:(id)fp12;
- (id)tableView:(id)fp8 namesOfPromisedFilesDroppedAtDestination:(id)fp12 forDraggedRowsWithIndexes:(id)fp16;
- (id)_dragImageForRow:(int)fp8 event:(id)fp12 dragImageOffset:(struct _NSPoint *)fp16;
- (id)tableView:(id)fp8 dragImageForRowsWithIndexes:(id)fp12 event:(id)fp16 dragImageOffset:(struct _NSPoint *)fp20;
- (void)tableView:(id)fp8 willDrawRowsInRange:(struct _NSRange)fp12;
- (void)tableView:(id)fp8 didDrawRowsInRange:(struct _NSRange)fp12;
- (struct _NSRect)frameOfClickedCell;
- (struct _NSPoint)mouseLocationInWindow;
- (void)callWillDisplayCellForClickedCell;
- (void)setButtonCellNeedsDisplay;
- (void)tableView:(id)fp8 gotEvent:(id)fp12;
- (BOOL)shouldTrackMouse:(id)fp8;
- (id)tableView:(id)fp8 rangesForBackgroundShadingInRange:(struct _NSRange)fp12 shadingColors:(id *)fp20 leftColumnColors:(id *)fp24;
- (id)messageMall;
- (int)_indexOfFirstNonDeletedNonSelectedMessage:(int)fp8 withinRowRange:(struct _NSRange)fp12 goUp:(BOOL)fp20;
- (id)messageBrowserView;
- (id)messageToSelectIfEntireSelectionRemoved;
- (BOOL)includeDeleted;
- (void)setIncludeDeleted:(BOOL)fp8;
- (id)noteFont;
- (id)boldFont;
- (void)setBoldFont:(id)fp8;
- (id)font;
- (id)draggedMessages;
- (void)setDraggedMessages:(id)fp8;

@end

@interface TableViewManager (AppleScript)
+ (id)_getDarkerThreadBackgroundColorForThread:(id)fp8;
+ (id)_getThreadBackgroundColorForThread:(id)fp8;
- (int)_columnForAppleScriptColumn:(int)fp8;
- (int)appleScriptSortColumn;
- (void)setAppleScriptSortColumn:(int)fp8;
- (id)appleScriptVisibleColumns;
- (void)setAppleScriptVisibleColumns:(id)fp8;
@end

@interface TableViewManager (FilteredList_Management)
- (void)mallStructureWillChange:(id)fp8;
- (void)setMailboxUids:(id)fp8 isSettingUpUI:(BOOL)fp12;
- (void)storeStructureChanged:(id)fp8;
- (void)messagesCompacted:(id)fp8;
- (void)messageFlagsChanged:(id)fp8;
- (void)_scrollToHappyPlace;
- (void)_recordVisibleState:(struct visible_state *)fp8 deletedAreGoingAway:(BOOL)fp12 considerPinToEnd:(BOOL)fp16;
- (BOOL)_restoreVisibleState:(struct visible_state *)fp8 forceSelToVisible:(BOOL)fp12;
- (void)dumpVisibleState;
- (int)indexOfTopmostVisibleMessageMustBeSelected:(BOOL)fp8 okayIfDeleted:(BOOL)fp12;
- (int)indexOfLastReadMessage;
- (id)persistentVisibleStateCreateIfNecessary:(BOOL)fp8;
- (void)_saveScrollAndSelection:(BOOL)fp8;
- (void)saveScrollAndSelection;
- (BOOL)restoreScrollAndSelection;
- (void)_setScrollAndSelectionForThreadOpenedOrClosed:(id)fp8 flag:(BOOL)fp12 clickedRow:(int)fp16 rowToSelectInOpeningThread:(int)fp20;
- (id)selectedMessageIDs;
- (id)openThreadIDs;
- (void)setSelectedMessageIDs:(id)fp8 openThreadIDs:(id)fp12;
- (void)clearSearch;
- (BOOL)isShowingSearchResults;
- (BOOL)rankColumnIsVisible;
- (void)searchForString:(id)fp8 in:(int)fp12 withOptions:(int)fp16;
- (BOOL)isFocused;
- (void)setFocusedMessages:(id)fp8;
- (BOOL)isSortedByRank;
- (BOOL)isSortedByDateReceived;
- (BOOL)isSortedChronologically;
- (int)sortColumn;
- (int)searchSortColumn;
- (void)setSortColumn:(int)fp8 ascending:(BOOL)fp12;
- (BOOL)isSortedAscending;
- (void)setIsSortedAscending:(BOOL)fp8;
- (BOOL)isSearchSortedAscending;
- (int)state;
- (id)filteredMessages;
- (void)clearTrackingRects;
- (void)updateTrackingRects;
- (int)_indexOfMemberToSelectWhenOpeningThread:(id)fp8;
- (double)_getAnimationDuration:(int)fp8;
- (id)_createHiliteImage;
- (id)_createBackgroundImage;
- (id)_createSnapshotOfRect:(struct _NSRect)fp8 styleMask:(unsigned int)fp24 backing:(unsigned int)fp28 defer:(BOOL)fp32;
- (id)_createSnapshotOfRow:(int)fp8 styleMask:(unsigned int)fp12 backing:(unsigned int)fp16 defer:(BOOL)fp20;
- (BOOL)_isRowVisible:(int)fp8;
- (struct _NSSize)_calculateTruncationAmountUsingRowHeight:(float)fp8 collapseOrExpandAmount:(float)fp12 invisibleThreadAmountAbove:(float)fp16 invisibleThreadAmountBelow:(float)fp20;
- (void)_animateThreadCollapsing:(int)fp8 threadRow:(int)fp12 clickedRow:(int)fp16;
- (float)_animateThreadOpening:(id)fp8 threadMessageCount:(int)fp12 threadRow:(int)fp16 rowToBeSelected:(int)fp20;
- (void)searchFinished:(id)fp8;
- (void)tableView:(id)fp8 willMoveToWindow:(id)fp12;
- (void)tableViewDidMoveToWindow:(id)fp8;
- (BOOL)selectMessageWithIDIfExists:(id)fp8;
@end

#elif defined(TIGER)

@class ASExtendedTableView;
@class MessageStore;
@class Message;
@class MessageMall;
@class MessageThread;
@class VisibleStateObject;

@protocol MVSelectionOwner
- (id)selection;
- (void)selectMessages:(id)fp8;
- (id)currentDisplayedMessage;
- (id)messageStore;
- (BOOL)transferSelectionToMailbox:(id)fp8 deleteOriginals:(BOOL)fp12;
@end

@protocol MessageBrowserController <NSObject, MVSelectionOwner>
- (id)messageBrowserView;
- (BOOL)isSelectionVisible;
- (void)showSelectionAndCenter:(BOOL)fp8;
- (void)updateTextViewerToSelection;
- (id)messagesToTransfer;
- (void)willTransferMessages:(id)fp8 toMailbox:(id)fp12 deleteOriginals:(BOOL)fp16;
- (void)transfer:(id)fp8 didCompleteWithError:(id)fp12;
- (id)messageToSelectIfEntireSelectionRemoved;
- (void)selectNextMessage:(BOOL)fp8;
- (void)selectPreviousMessage:(BOOL)fp8;
- (void)selectNextMessageMovingDownward:(BOOL)fp8;
- (void)selectNextMessageMovingUpward:(BOOL)fp8;
- (BOOL)includeDeleted;
- (void)setIncludeDeleted:(BOOL)fp8;
- (BOOL)shouldDeleteGivenCurrentState;
- (void)deleteSelectionAllowingMoveToTrash:(BOOL)fp8;
- (void)deleteMessages:(id)fp8 allowMoveToTrash:(BOOL)fp12 allowUndo:(BOOL)fp16;
- (void)undeleteMessagesAllowingUndo:(BOOL)fp8;
- (void)undeleteMessages:(id)fp8 allowUndo:(BOOL)fp12;
@end

@interface TableViewManager : NSObject <MessageBrowserController>
{
    ASExtendedTableView *_tableView;
    MessageMall *_messageMall;
    id _delegate;
    NSArray *_tableColumns;
    NSFont *_font;
    NSFont *_boldFont;
    NSMutableArray *_selection;
    NSArray *_selectionExcludingThreads;
    BOOL _suspendChangesToScrollingAndSelection;
    Message *_currentDisplayedMessage;
    struct _NSMapTable *_storeStateTable;
    NSMutableArray *_draggedMessages;
    NSMutableAttributedString *_truncatedString;
    NSMutableDictionary *_truncatedParagraphStyle;
    NSString *_availableStatusImageName;
    int leftmostTextColumn;
    struct {
        unsigned int includeDeleted:1;
        unsigned int isFocused:1;
        unsigned int wasSortedAscendingBeforeRankSort:1;
        unsigned int isShowingSearchResults:1;
        unsigned int sortColumnBeforeRankSort:8;
        unsigned int showAccountInLocationColumn:1;
        unsigned int showSenderColumnAlways:1;
        unsigned int hideSenderColumnAlways:1;
        unsigned int showReceiverColumnAlways:1;
        unsigned int hideReceiverColumnAlways:1;
        unsigned int showDateReceivedColumnAlways:1;
        unsigned int hideDateReceivedColumnAlways:1;
        unsigned int showDateSentColumnAlways:1;
        unsigned int hideDateSentColumnAlways:1;
        unsigned int showDateLastViewedColumnAlways:1;
        unsigned int hideDateLastViewedColumnAlways:1;
        unsigned int showLocationColumn:1;
        unsigned int hasScrolledSinceMailboxChange:1;
        unsigned int userChangedSelectionSinceMailboxChange:1;
        unsigned int threadOpeningIsInProgress:1;
        unsigned int threadClosingIsInProgress:1;
        unsigned int doubleClickThreadOpeningIsInProgress:1;
        unsigned int animatingThreadOpening:1;
        unsigned int animatingThreadClosing:1;
        unsigned int animateInSlowMotion:1;
        unsigned int dontUpdateTrackingRects:1;
        unsigned int dontReadWriteStoreSpecificDefaultsToMailbox:1;
        unsigned int useBoldFontForUnreadMessages:1;
        unsigned int clearingSearch:1;
        unsigned int changingSelection:1;
        unsigned int selectionShouldNotChange:1;
    } _flags;
    NSDictionary *_messageIDsToSelectWhenOpened;
    NSArray *_threadIDsToOpenWhenOpened;
    int colorHighlightLeftEdge;
    int colorHighlightWidth;
    int locationColumnPosition;
    int locationColumnWidth;
    int senderColumnPosition;
    int senderColumnWidth;
    int receiverColumnPosition;
    int receiverColumnWidth;
    int dateReceivedColumnPosition;
    int dateReceivedColumnWidth;
    int dateSentColumnPosition;
    int dateSentColumnWidth;
    int dateLastViewedColumnPosition;
    int dateLastViewedColumnWidth;
    int threadedUnreadColumnWidth;
    NSMutableDictionary *_columnWidthsBeforeSearch;
    int _windowWidthBeforeSearch;
    VisibleStateObject *_visibleStateBeforeSearch;
    NSMutableSet *_messagesInSelectedThread;
    MessageThread *threadBeingClosed;
    MessageThread *threadBeingOpened;
    struct __CFDictionary *_rowDrawingCache;
    NSMutableSet *_mouseTrackers;
    struct _NSPoint _lastMouseDownInUnreadColumnPoint;
    int _lastMouseDownInUnreadColumnEventNumber;
    struct _NSPoint _currentMouseLocationInWindow;
    float _amountToScrollDownAfterClosingThread;
    int _numberOfSelectedRowsBeforeTogglingThread;
    int _selectedRowBeforeTogglingThread;
    BOOL _unreadColumnResizableAfterResizingColumnsToFit;
}

+ (void)initialize;
- (void)awakeFromNib;
- (void)tableViewScrolled:(id)fp8;
- (void)_setupColumnHeaderIcon:(id)fp8 inColumnWithIdentifier:(id)fp12 accessibilityTitle:(id)fp16 alignment:(int)fp20;
- (int)_calcUnreadColumnWidthForUnreadCountString:(id)fp8;
- (void)_setupUnreadColumnMinWidth;
- (void)_setupUnreadColumnWidth;
- (void)_setupTableColumnWidths;
- (void)_configureColumnForEndTruncation:(id)fp8;
- (void)_configureColumnForDateCell:(id)fp8;
- (void)_configureColumnForImageCell:(id)fp8 alignment:(int)fp12;
- (void)_configureColumnForRolloverCell:(id)fp8 alignment:(int)fp12 action:(SEL)fp16;
- (void)showFollowupsToMessage:(id)fp8;
- (void)showFollowupsToMessageAtRow:(int)fp8;
- (void)_setupColumnsForTableView;
- (void)dealloc;
- (void)windowWillClose:(id)fp8;
- (id)delegate;
- (void)setDelegate:(id)fp8;
- (void)setMessageMall:(id)fp8;
- (void)readDefaultsFromDictionary:(id)fp8;
- (void)readColumnLayoutFromDictionary:(id)fp8;
- (void)writeDefaultsToDictionary:(id)fp8;
- (void)writeColumnLayoutToDictionary:(id)fp8;
- (void)setDontReadWriteStoreSpecificDefaultsToMailbox:(BOOL)fp8;
- (void)writeStoreSpecificDefaultsToMailboxUid:(id)fp8;
- (void)readStoreSpecificDefaultsFromMailboxUid:(id)fp8;
- (void)readStoreSpecificDefaultsFromDictionary:(id)fp8;
- (BOOL)canSelectNextMessage;
- (BOOL)canSelectPreviousMessage;
- (void)rulePreferencesChanged:(id)fp8;
- (void)viewerPreferencesChanged:(id)fp8;
- (BOOL)threadHasSelectedMessages:(id)fp8;
- (void)presencePreferenceChanged:(id)fp8;
- (void)threadColorPreferenceChanged:(id)fp8;
- (void)presenceImageChanged:(id)fp8;
- (void)presenceChanged:(id)fp8;
- (void)_updateTableHeaderToMatchCurrentSort;
- (void)tableView:(id)fp8 didClickTableColumn:(id)fp12;
- (id)_columnWithIdentifierTag:(int)fp8;
- (id)_unreadColumn;
- (BOOL)isColumnVisible:(int)fp8;
- (void)setColumn:(int)fp8 toVisible:(BOOL)fp12;
- (void)_setColumn:(int)fp8 toVisible:(BOOL)fp12;
- (BOOL)displaysMessageSizes;
- (void)setDisplaysReceiver:(BOOL)fp8 displaysDateSent:(BOOL)fp12 displaysDateLastViewed:(BOOL)fp16;
- (int)tableViewNumberOfColumnsToPinToLefthandSide:(id)fp8;
- (void)selectAllMessagesAndMakeFirstResponder;
- (void)makeMessageListFirstResponder;
- (void)setFont:(id)fp8;
- (id)font;
- (id)boldFont;
- (BOOL)isInThreadedMode;
- (void)toggleThreadedMode;
- (void)threadedModeDidChange:(id)fp8;
- (void)_invalidateSelectionExcludingThreads;
- (void)openThreadAtIndex:(int)fp8 andSelectMessage:(id)fp12 animate:(BOOL)fp16;
- (void)closeThreadAtIndex:(int)fp8 focusRow:(int)fp12 animate:(BOOL)fp16;
- (void)openAllThreads;
- (void)closeAllThreads;
- (void)toggleThread:(id)fp8;
- (void)toggleThread:(id)fp8 ignoreModifierKeys:(BOOL)fp12;
- (int)_indexOfMessageNearest:(int)fp8 numberOfRows:(int)fp12 threaded:(BOOL)fp16 downward:(BOOL)fp20;
- (BOOL)canSelectPreviousThreadedMessage;
- (BOOL)canSelectNextThreadedMessage;
- (BOOL)canSelectParentOfMessage;
- (BOOL)canSelectFirstReplyToMessage;
- (BOOL)canSelectNextReplyToParent;
- (BOOL)selectionIsExactlyOneOpenThread;
- (void)selectNextMessageMovingDownward:(BOOL)fp8;
- (void)selectNextMessageMovingUpward:(BOOL)fp8;
- (void)stepIntoSelectedThread;
- (void)stepOutOfSelectedThread;
- (BOOL)openSelectedThread;
- (void)selectNextMessage:(BOOL)fp8;
- (void)selectPreviousMessage:(BOOL)fp8;
- (void)selectParentOfMessage;
- (void)selectFirstReplyToMessage;
- (void)selectPeer:(BOOL)fp8;
- (void)selectNextReplyToParent;
- (void)selectPreviousReplyToParent;
- (void)showSelectionAndCenter:(BOOL)fp8;
- (BOOL)isSelectionVisible;
- (void)scrollRowToVisible:(int)fp8 position:(int)fp12;
- (int)tableView:(id)fp8 shouldScrollRowToVisible:(int)fp12;
- (BOOL)_isMessageInSelectedThread:(id)fp8;
- (void)_setNeedsDisplayForMessagesInSet:(id)fp8;
- (void)_setNeedsDisplayThreadColumnForMessagesInSet:(id)fp8;
- (void)_updateSelectedThreadList;
- (id)selectedThread;
- (void)_reallyUpdateTextViewerToSelection;
- (void)updateTextViewerToSelection;
- (BOOL)tableView:(id)fp8 shouldSelectRow:(int)fp12 byExtendingSelection:(BOOL)fp16;
- (void)selectionIsChanging:(id)fp8;
- (void)_selectOrDeselectMembersOfThread:(id)fp8 atIndex:(int)fp12 select:(BOOL)fp16;
- (void)selectionChanged:(id)fp8;
- (void)datesNeedRedisplay;
- (int)numberOfRowsInTableView:(id)fp8;
- (id)_attributesForTruncatedParagraphStyle;
- (id)_colorForMessage:(id)fp8 inRow:(int)fp12;
- (id)_truncatedAttributedStringForString:(id)fp8 message:(id)fp12 row:(int)fp16 shouldIndent:(BOOL)fp20;
- (id)tableView:(id)fp8 sampleObjectValueForTableColumn:(id)fp12 row:(int)fp16;
- (id)tableView:(id)fp8 objectValueForTableColumn:(id)fp12 row:(int)fp16;
- (void)_updateColorHighlightEdges;
- (void)tableView:(id)fp8 didDragTableColumn:(id)fp12;
- (void)tableViewColumnDidMove:(id)fp8;
- (void)tableViewColumnDidResize:(id)fp8;
- (void)tableView:(id)fp8 willDisplaySampleCell:(id)fp12 forTableColumn:(id)fp16 row:(int)fp20;
- (void)tableView:(id)fp8 willDisplayCell:(id)fp12 forTableColumn:(id)fp16 row:(int)fp20;
- (id)tableViewHighlightColor:(id)fp8;
- (int)tableView:(id)fp8 highlightStyleForRow:(int)fp12 inRect:(struct _NSRect *)fp16 color:(id *)fp20;
- (void)doubleClickedMessage:(id)fp8;
- (void)deleteKeyPressed;
- (void)deleteSelectionAllowingMoveToTrash:(BOOL)fp8;
- (id)selectionIncludingThreads:(BOOL)fp8;
- (id)selection;
- (void)_selectMessages:(id)fp8 scrollIfNeeded:(BOOL)fp12;
- (void)selectMessages:(id)fp8;
- (id)currentDisplayedMessage;
- (id)messageStore;
- (id)orderOfFromSubjectDateColumns;
- (id)tableView;
- (BOOL)tableView:(id)fp8 doCommandBySelector:(SEL)fp12;
- (id)_undoActionNameForMessages:(id)fp8;
- (void)_undeleteMessages:(id)fp8 allowUndo:(BOOL)fp12 unreadMessages:(id)fp16;
- (id)_unreadMessagesFromMessages:(id)fp8;
- (void)undeleteMessages:(id)fp8 allowUndo:(BOOL)fp12;
- (void)_redeleteMessages:(id)fp8 messagesToSelect:(id)fp12;
- (void)deleteMessages:(id)fp8 allowMoveToTrash:(BOOL)fp12 allowUndo:(BOOL)fp16;
- (void)undeleteMessagesAllowingUndo:(BOOL)fp8;
- (BOOL)shouldDeleteGivenCurrentState;
- (void)tableViewDraggedImage:(id)fp8 movedTo:(struct _NSPoint)fp12;
- (unsigned int)tableView:(id)fp8 draggingSourceOperationMaskForLocal:(BOOL)fp12;
- (id)messagesToTransfer;
- (void)willTransferMessages:(id)fp8 toMailbox:(id)fp12 deleteOriginals:(BOOL)fp16;
- (void)transfer:(id)fp8 didCompleteWithError:(id)fp12;
- (BOOL)transferSelectionToMailbox:(id)fp8 deleteOriginals:(BOOL)fp12;
- (void)tableViewDragWillEnd:(id)fp8 operation:(unsigned int)fp12;
- (BOOL)tableView:(id)fp8 writeRows:(id)fp12 toPasteboard:(id)fp16;
- (id)_dragImageForRow:(int)fp8 event:(id)fp12 dragImageOffset:(struct _NSPoint *)fp16;
- (id)tableView:(id)fp8 dragImageForRowsWithIndexes:(id)fp12 event:(id)fp16 dragImageOffset:(struct _NSPoint *)fp20;
- (void)tableView:(id)fp8 willDrawRowsInRange:(struct _NSRange)fp12;
- (void)tableView:(id)fp8 didDrawRowsInRange:(struct _NSRange)fp12;
- (struct _NSRect)frameOfClickedCell;
- (struct _NSPoint)mouseLocationInWindow;
- (void)callWillDisplayCellForClickedCell;
- (void)setButtonCellNeedsDisplay;
- (void)tableView:(id)fp8 gotEvent:(id)fp12;
- (BOOL)shouldTrackMouse:(id)fp8;
- (id)tableView:(id)fp8 rangesForBackgroundShadingInRange:(struct _NSRange)fp12 shadingColors:(id *)fp20 leftColumnColors:(id *)fp24;
- (id)messageMall;
- (int)_indexOfFirstNonDeletedNonSelectedMessage:(int)fp8 withinRowRange:(struct _NSRange)fp12 goUp:(BOOL)fp20;
- (id)messageBrowserView;
- (id)messageToSelectIfEntireSelectionRemoved;
- (BOOL)includeDeleted;
- (void)setIncludeDeleted:(BOOL)fp8;

@end

@interface TableViewManager (AppleScript)
+ (id)_getDarkerThreadBackgroundColorForThread:(id)fp8;
+ (id)_getThreadBackgroundColorForThread:(id)fp8;
- (int)_columnForAppleScriptColumn:(int)fp8;
- (int)appleScriptSortColumn;
- (void)setAppleScriptSortColumn:(int)fp8;
- (id)appleScriptVisibleColumns;
- (void)setAppleScriptVisibleColumns:(id)fp8;
@end

@interface TableViewManager (FilteredList_Management)
- (void)mallStructureWillChange:(id)fp8;
- (void)setMailboxUids:(id)fp8;
- (BOOL)_allMailboxes:(id)fp8 areOfTypes:(int *)fp12 typeCount:(unsigned int)fp16;
- (BOOL)allMailboxesAreOutgoing:(id)fp8;
- (BOOL)allMailboxes:(id)fp8 areOfType:(int)fp12;
- (BOOL)_criterionIsLastViewedDate:(id)fp8;
- (BOOL)mailboxIsViewingHistorySmartMailbox:(id)fp8;
- (BOOL)allMailboxesAreViewingHistorySmartMailboxes:(id)fp8;
- (void)storeStructureChanged:(id)fp8;
- (void)messagesCompacted:(id)fp8;
- (void)messageFlagsChanged:(id)fp8;
- (void)_scrollToHappyPlace;
- (void)_recordVisibleState:(struct visible_state *)fp8 deletedAreGoingAway:(BOOL)fp12 considerPinToEnd:(BOOL)fp16;
- (BOOL)_restoreVisibleState:(struct visible_state *)fp8 forceSelToVisible:(BOOL)fp12;
- (void)dumpVisibleState;
- (int)indexOfTopmostVisibleMessageMustBeSelected:(BOOL)fp8 okayIfDeleted:(BOOL)fp12;
- (int)indexOfLastReadMessage;
- (id)persistentVisibleStateCreateIfNecessary:(BOOL)fp8;
- (void)_saveScrollAndSelection:(BOOL)fp8;
- (void)saveScrollAndSelection;
- (BOOL)restoreScrollAndSelection;
- (void)_setScrollAndSelectionForThreadOpenedOrClosed:(id)fp8 flag:(BOOL)fp12 clickedRow:(int)fp16 rowToSelectInOpeningThread:(int)fp20;
- (id)selectedMessageIDs;
- (id)openThreadIDs;
- (void)setSelectedMessageIDs:(id)fp8 openThreadIDs:(id)fp12;
- (void)addRanks;
- (void)removeRanks;
- (void)clearSearch;
- (BOOL)isShowingSearchResults;
- (void)searchForString:(id)fp8 in:(int)fp12 withOptions:(int)fp16;
- (BOOL)isFocused;
- (void)setFocusedMessages:(id)fp8;
- (BOOL)isSortedByRank;
- (BOOL)isSortedByDateReceived;
- (BOOL)isSortedChronologically;
- (int)sortColumn;
- (void)setSortColumn:(int)fp8 ascending:(BOOL)fp12;
- (BOOL)isSortedAscending;
- (void)setIsSortedAscending:(BOOL)fp8;
- (int)state;
- (id)filteredMessages;
- (void)restoreLocationColumnIfAppropriate;
- (void)clearTrackingRects;
- (void)updateTrackingRects;
- (int)_indexOfMemberToSelectWhenOpeningThread:(id)fp8;
- (double)_getAnimationDuration:(int)fp8;
- (id)_createHiliteImage;
- (id)_createBackgroundImage;
- (id)_createSnapshotOfRect:(struct _NSRect)fp8 styleMask:(unsigned int)fp24 backing:(int)fp28 defer:(BOOL)fp32;
- (id)_createSnapshotOfRow:(int)fp8 styleMask:(unsigned int)fp12 backing:(int)fp16 defer:(BOOL)fp20;
- (BOOL)_isRowVisible:(int)fp8;
- (struct _NSSize)_calculateTruncationAmountUsingRowHeight:(float)fp8 collapseOrExpandAmount:(float)fp12 invisibleThreadAmountAbove:(float)fp16 invisibleThreadAmountBelow:(float)fp20;
- (void)_animateThreadCollapsing:(int)fp8 threadRow:(int)fp12 clickedRow:(int)fp16;
- (float)_animateThreadOpening:(id)fp8 threadMessageCount:(int)fp12 threadRow:(int)fp16 rowToBeSelected:(int)fp20;
- (void)searchFinished:(id)fp8;
- (void)tableView:(id)fp8 willMoveToWindow:(id)fp12;
- (void)tableViewDidMoveToWindow:(id)fp8;
- (BOOL)selectMessageWithIDIfExists:(id)fp8;
@end

#else

@class ASExtendedTableView;
@class MessageStore;
@class Message;
@class MessageMall;
@class MessageThread;

@protocol MVSelectionOwner
- (char)transferSelectionToMailbox:fp8 deleteOriginals:(char)fp12;
- messageStore;
- currentDisplayedMessage;
- (void)selectMessages:fp8;
- selection;
@end

@interface TableViewManager:NSObject <MVSelectionOwner>
{
    ASExtendedTableView *_tableView;	// 4 = 0x4
    MessageMall *_messageMall;	// 8 = 0x8
    id _delegate;	// 12 = 0xc
    NSArray *_tableColumns;	// 16 = 0x10
    NSFont *_font;	// 20 = 0x14
    NSMutableArray *_selection;	// 24 = 0x18
    char _suspendChangesToScrollingAndSelection;	// 28 = 0x1c
    Message *_currentDisplayedMessage;	// 32 = 0x20
    struct _NSMapTable *_storeStateTable;	// 36 = 0x24
    NSMutableArray *_draggedMessages;	// 40 = 0x28
    NSMutableAttributedString *_truncatedString;	// 44 = 0x2c
    NSMutableDictionary *_truncatedParagraphStyle;	// 48 = 0x30
    int leftmostTextColumn;	// 52 = 0x34
    struct {
        int includeDeleted:1;
        int isFocused:1;
        int wasSortedAscendingBeforeRankSort:1;
        int isShowingSearchResults:1;
        int sortColumnBeforeRankSort:8;
        int showAccountInLocationColumn:1;
        int showSenderColumnAlways:1;
        int hideSenderColumnAlways:1;
        int showReceiverColumnAlways:1;
        int hideReceiverColumnAlways:1;
        int showLocationColumn:1;
        int hasScrolledSinceMailboxChange:1;
        int userChangedSelectionSinceMailboxChange:1;
        int threadOpeningIsInProgress:1;
        int threadClosingIsInProgress:1;
        int doubleClickThreadOpeningIsInProgress:1;
        int animatingThreadOpening:1;
        int animatingThreadClosing:1;
        unsigned int animateInSlowMotion;
        unsigned int dontUpdateTrackingRects;
    } _flags;	// 56 = 0x38
    NSDictionary *_messageIDsToSelectWhenOpened;	// 68 = 0x44
    NSArray *_threadIDsToOpenWhenOpened;	// 72 = 0x48
    int colorHighlightLeftEdge;	// 76 = 0x4c
    int colorHighlightWidth;	// 80 = 0x50
    int locationColumnPosition;	// 84 = 0x54
    int locationColumnWidth;	// 88 = 0x58
    int senderColumnPosition;	// 92 = 0x5c
    int senderColumnWidth;	// 96 = 0x60
    int receiverColumnPosition;	// 100 = 0x64
    int receiverColumnWidth;	// 104 = 0x68
    int threadedUnreadColumnWidth;	// 108 = 0x6c
    NSMutableDictionary *_columnWidthsBeforeSearch;	// 112 = 0x70
    int _windowWidthBeforeSearch;	// 116 = 0x74
    NSMutableSet *_messagesInSelectedThread;	// 120 = 0x78
    MessageThread *threadBeingClosed;	// 124 = 0x7c
    MessageThread *threadBeingOpened;	// 128 = 0x80
    struct __CFDictionary *_rowDrawingCache;	// 132 = 0x84
    NSMutableSet *_mouseTrackers;	// 136 = 0x88
    struct _NSPoint _lastMouseDownInUnreadColumnPoint;	// 140 = 0x8c
    int _lastMouseDownInUnreadColumnEventNumber;	// 148 = 0x94
    struct _NSPoint _currentMouseLocationInWindow;	// 152 = 0x98
    float _amountToScrollDownAfterClosingThread;	// 160 = 0xa0
    int _numberOfSelectedRowsBeforeTogglingThread;	// 164 = 0xa4
    int _selectedRowBeforeTogglingThread;	// 168 = 0xa8
    char _unreadColumnResizableAfterResizingColumnsToFit;	// 172 = 0xac
}

+ (void)initialize;
- (void)awakeFromNib;
- (void)tableViewScrolled:fp8;
- (void)_setupColumnHeaderIcon:fp8 inColumnWithIdentifier:fp12 alignment:(int)fp16;
- (int)_calcUnreadColumnWidthForUnreadCountString:fp8;
- (void)_setupUnreadColumnMinWidth;
- (void)_setupUnreadColumnWidth;
- (void)_setupTableColumnWidths;
- (void)_configureColumnForEndTruncation:fp8;
- (void)_configureColumnForDateCell:fp8;
- (void)_configureColumnForImageCell:fp8 alignment:(int)fp12;
- (void)_configureColumnForRolloverCell:fp8 alignment:(int)fp12 action:(SEL)fp16;
- (void)showFollowupsToMessage:fp8;
- (void)_setupColumnsForTableView;
- (void)dealloc;
- (void)windowWillClose:fp8;
- delegate;
- (void)setMessageMall:fp8;
- (void)readDefaultsFromDictionary:fp8;
- (void)writeDefaultsToDictionary:fp8;
- (void)writeStoreSpecificDefaultsToMailboxUid:fp8;
- (void)readStoreSpecificDefaultsFromMailboxUid:fp8;
- (void)readStoreSpecificDefaultsFromDictionary:fp8;
- (char)canSelectNextMessage;
- (char)canSelectPreviousMessage;
- (void)rulePreferencesChanged:fp8;
- (void)viewerPreferencesChanged:fp8;
- (char)threadHasSelectedMessages:fp8;
- (void)presencePreferenceChanged:fp8;
- (void)presenceChanged:fp8;
- (void)_updateTableHeaderToMatchCurrentSort;
- (void)tableView:fp8 didClickTableColumn:fp12;
- _columnWithIdentifierTag:(int)fp8;
- _unreadColumn;
- (char)isColumnVisible:(int)fp8;
- (void)setColumn:(int)fp8 toVisible:(char)fp12;
- (void)_setColumn:(int)fp8 toVisible:(char)fp12;
- (char)displaysMessageSizes;
- (void)setDisplaysReceiver:(char)fp8;
- (int)tableViewNumberOfColumnsToPinToLefthandSide:fp8;
- (void)tableViewWillResizeColumnsToFit:fp8;
- (void)tableViewDidResizeColumnsToFit:fp8;
- (void)setFont:fp8;
- font;
- (char)isInThreadedMode;
- (void)toggleThreadedMode;
- (void)threadedModeDidChange:fp8;
- (void)openThreadAtIndex:(int)fp8 andSelectMessage:fp12 animate:(char)fp16;
- (void)closeThreadAtIndex:(int)fp8 focusRow:(int)fp12 animate:(char)fp16;
- (void)openAllThreads;
- (void)closeAllThreads;
- (void)toggleThread:fp8;
- (int)_indexOfMessageNearest:(int)fp8 numberOfRows:(int)fp12 threaded:(char)fp16 downward:(char)fp20;
- (char)canSelectPreviousThreadedMessage;
- (char)canSelectNextThreadedMessage;
- (char)canSelectParentOfMessage;
- (char)canSelectFirstReplyToMessage;
- (char)canSelectNextReplyToParent;
- (char)selectionIsExactlyOneOpenThread;
- (void)selectNextMessageMovingDownward:(char)fp8;
- (void)selectNextMessageMovingUpward:(char)fp8;
- (void)stepIntoSelectedThread;
- (void)stepOutOfSelectedThread;
- (void)selectNextMessage:(char)fp8;
- (void)selectPreviousMessage:(char)fp8;
- (void)selectParentOfMessage;
- (void)selectFirstReplyToMessage;
- (void)selectPeer:(char)fp8;
- (void)selectNextReplyToParent;
- (void)selectPreviousReplyToParent;
- (void)showSelectionAndCenter:(char)fp8;
- (char)isSelectionVisible;
- (void)scrollRowToVisible:(int)fp8 position:(int)fp12;
- (int)tableView:fp8 shouldScrollRowToVisible:(int)fp12;
- (char)_isMessageInSelectedThread:fp8;
- (void)_setNeedsDisplayForMessagesInSet:fp8;
- (void)_setNeedsDisplayThreadColumnForMessagesInSet:fp8;
- (void)_updateSelectedThreadList;
- selectedThread;
- (void)_reallyUpdateTextViewerToSelection;
- (void)updateTextViewerToSelection;
- (char)tableView:fp8 shouldSelectRow:(int)fp12 byExtendingSelection:(char)fp16;
- (void)selectionIsChanging:fp8;
- (void)selectionChanged:fp8;
- (void)datesNeedRedisplay;
- (void)antialiasingSettingsChanged:fp8;
- (int)numberOfRowsInTableView:fp8;
- _attributesForTruncatedParagraphStyle;
- _colorForMessage:fp8 inRow:(int)fp12;
- _truncatedAttributedStringForString:fp8 message:fp12 row:(int)fp16 shouldIndent:(char)fp20;
- tableView:fp8 objectValueForTableColumn:fp12 row:(int)fp16;
- (void)_updateColorHighlightEdges;
- (void)tableView:fp8 didDragTableColumn:fp12;
- (void)tableViewColumnDidMove:fp8;
- (void)tableViewColumnDidResize:fp8;
- (void)tableView:fp8 willDisplayCell:fp12 forTableColumn:fp16 row:(int)fp20;
- tableViewHighlightColor:fp8;
- (int)tableView:fp8 highlightStyleForRow:(int)fp12 inRect:(struct _NSRect *)fp16 color:(id *)fp20;
- (void)doubleClickedMessage:fp8;
- (void)deleteKeyPressed;
- (void)deleteSelectionAllowingMoveToTrash:(char)fp8;
- selectionIncludingThreads:(char)fp8;
- selection;
- (void)_selectMessages:fp8 scrollIfNeeded:(char)fp12;
- (void)selectMessages:fp8;
- currentDisplayedMessage;
- messageStore;
- orderOfFromSubjectDateColumns;
- tableView;
- (char)tableView:fp8 doCommandBySelector:(SEL)fp12;
- _undoActionNameForMessages:fp8;
- (void)undeleteMessages:fp8 allowUndo:(char)fp12;
- (void)_redeleteMessages:fp8 messagesToSelect:fp12;
- (void)deleteMessages:fp8 allowMoveToTrash:(char)fp12 allowUndo:(char)fp16;
- (void)deleteMessages:fp8 allowMoveToTrash:(char)fp12;
- (void)undeleteMessagesAllowingUndo:(char)fp8;
- (void)undeleteMessages;
- (void)undeleteMessages:fp8;
- (char)shouldDeleteGivenCurrentState;
- (unsigned int)tableView:fp8 draggingSourceOperationMaskForLocal:(char)fp12;
- messagesToTransfer;
- (char)transferSelectionToMailbox:fp8 deleteOriginals:(char)fp12;
- (void)tableViewDragWillEnd:fp8 operation:(unsigned int)fp12;
- (char)tableView:fp8 writeRows:fp12 toPasteboard:fp16;
- _dragImageForRow:(int)fp8 event:fp12 dragImageOffset:(struct _NSPoint *)fp16;
- _badgeImageFromItemCount:(int)fp8;
- tableView:fp8 dragImageForRows:fp12 event:fp16 dragImageOffset:(struct _NSPoint *)fp20;
- tableViewRowIdForRow:(int)fp8;
- (void)tableView:fp8 willDrawRowsInRange:(struct _NSRange)fp12;
- (void)tableView:fp8 didDrawRowsInRange:(struct _NSRange)fp12;
- (struct _NSRect)frameOfClickedCell;
- (struct _NSPoint)mouseLocationInWindow;
- (void)callWillDisplayCellForClickedCell;
- (void)setButtonCellNeedsDisplay;
- (void)tableView:fp8 gotEvent:fp12;
- (char)shouldTrackMouse:fp8;
- (char)tableView:fp8 shouldBeginDragFromMouseDown:fp12;
- tableView:fp8 rangesForBackgroundShadingInRange:(struct _NSRange)fp12 shadingColors:(id *)fp20 leftColumnColors:(id *)fp24;
- messageMall;

@end

@interface TableViewManager(AppleScript)
+ _getDarkerThreadBackgroundColorForThread:fp8;
+ _getThreadBackgroundColorForThread:fp8;
- (int)_columnForAppleScriptColumn:(int)fp8;
- (int)appleScriptSortColumn;
- (void)setAppleScriptSortColumn:(int)fp8;
- appleScriptVisibleColumns;
- (void)setAppleScriptVisibleColumns:fp8;
@end

@interface TableViewManager(FilteredList_Management)
- (void)mallStructureWillChange:fp8;
- (void)setMailboxUids:fp8;
- (char)allMailboxesAreOutgoing:fp8;
- (void)storeStructureChanged:fp8;
- (void)messagesCompacted:fp8;
- (void)messageFlagsChanged:fp8;
- (void)_scrollToHappyPlace;
- (void)_recordVisibleState:(struct visible_state *)fp8 deletedAreGoingAway:(char)fp12 considerPinToEnd:(char)fp16;
- (char)_restoreVisibleState:(struct visible_state *)fp8 forceSelToVisible:(char)fp12;
- (void)dumpVisibleState;
- _messageToSelectIfEntireSelectionRemoved;
- (int)indexOfTopmostVisibleMessageMustBeSelected:(char)fp8 okayIfDeleted:(char)fp12;
- (int)indexOfLastReadMessage;
- (int)indexOfFirstNonDeletedNonSelectedMessage:(int)fp8 withinRowRange:(struct _NSRange)fp12 goUp:(char)fp20;
- persistentVisibleStateCreateIfNecessary:(char)fp8;
- (void)saveScrollAndSelection;
- (char)restoreScrollAndSelection;
- (void)_setScrollAndSelectionForThreadOpenedOrClosed:fp8 flag:(char)fp12 clickedRow:(int)fp16 rowToSelectInOpeningThread:(int)fp20;
- selectedMessageIDs;
- openThreadIDs;
- (void)setSelectedMessageIDs:fp8 openThreadIDs:fp12;
- (void)addRanks;
- (void)removeRanks;
- (void)clearSearch;
- (char)isShowingSearchResults;
- (void)searchForString:fp8 in:(int)fp12 withOptions:(int)fp16;
- (char)isFocused;
- (void)setFocusedMessages:fp8;
- (char)includeDeleted;
- (void)setIncludeDeleted:(char)fp8;
- (char)isSortedByRank;
- (char)isSortedByDateReceived;
- (char)isSortedChronologically;
- (int)sortColumn;
- (void)setSortColumn:(int)fp8 ascending:(char)fp12;
- (char)isSortedAscending;
- (void)setIsSortedAscending:(char)fp8;
- (int)state;
- filteredMessages;
- (void)restoreLocationColumnIfAppropriate;
- (void)clearTrackingRects;
- (void)updateTrackingRects;
- (void)mouseTrackerDidUpdate:fp8;
- (int)_indexOfMemberToSelectWhenOpeningThread:fp8;
- (double)_getAnimationDuration:(int)fp8;
- _createHiliteImage;
- _createBackgroundImage;
- _createSnapshotOfRect:(struct _NSRect)fp8 styleMask:(unsigned int)fp24 backing:(int)fp28 defer:(char)fp32;
- _createSnapshotOfRow:(int)fp8 styleMask:(unsigned int)fp12 backing:(int)fp16 defer:(char)fp20;
- (void)_clearImageCacheForMessage:fp8;
- (void)_clearImageCacheForRow:(int)fp8;
- (char)_isRowVisible:(int)fp8;
- (struct _NSSize)_calculateTruncationAmountUsingRowHeight:(float)fp8 collapseOrExpandAmount:(float)fp12 invisibleThreadAmountAbove:(float)fp16 invisibleThreadAmountBelow:(float)fp20;
- (void)_animateThreadCollapsing:(int)fp8 threadRow:(int)fp12 clickedRow:(int)fp16;
- (float)_animateThreadOpening:fp8 threadMessageCount:(int)fp12 threadRow:(int)fp16 rowToBeSelected:(int)fp20;
@end

#endif
