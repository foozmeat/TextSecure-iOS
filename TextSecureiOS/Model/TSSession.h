//
//  TSSession.h
//  TextSecureiOS
//
//  Created by Frederic Jacobs on 01/03/14.
//  Copyright (c) 2014 Open Whisper Systems. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TSContact.h"
#import "RKCK.h"
#import "TSMessageKeys.h"
#import "TSPrekey.h"
#import "TSChainKey.h"
#import "TSEncryptedWhisperMessage.hh"

@interface TSSession : NSObject

- (instancetype)initWithContact:(TSContact*)contact deviceId:(int)deviceId;

@property(readonly)int deviceId;
@property(readonly)TSContact *contact;

@property(copy)NSData *theirEphemeralKey;
@property(readwrite)NSData *rootKey;

@property NSData *ephemeralReceiving;
@property TSECKeyPair *senderEphemeral;
@property int PN;

@property TSPrekey *preKey;

#pragma mark Prekey methods (non-persistent)

- (BOOL)hasPendingPrekey;
- (TSPrekey*)pendingPrekey;

- (BOOL)hasReceiverChain:(NSData*) ephemeral;
- (BOOL)hasSenderChain;

- (TSChainKey*)receiverChainKey:(NSData*)senderEphemeral;

- (void)setSenderChain:(TSECKeyPair*)senderEphemeralPair chainkey:(TSChainKey*)chainKey;
- (void)setSenderChainKey:(TSChainKey*)chainKey;
- (TSChainKey*)senderChainKey;

- (void)addReceiverChain:(NSData*)senderEphemeral chainKey:(TSChainKey*)chainKey;
- (void)setReceiverChainKeyWithEphemeral:(NSData*)senderEphemeral chainKey:(TSChainKey*)chainKey;

- (BOOL)hasMessageKeysForEphemeral:(NSData*)ephemeral counter:(int)counter;
- (void)removeMessageKeysForEphemeral:(NSData*)ephemeral counter:(int)counter;

- (void)setMessageKeysWithEphemeral:(NSData*)ephemeral messageKey:(TSMessageKeys*)messageKeys;

#pragma mark Helper methods
- (NSData*)theirIdentityKey;


- (void)save;

/**
 *  The clear method removes all keying material of a session. Only properties remaining are the necessary deviceId and contact information
 */

- (void)clear;

@end
