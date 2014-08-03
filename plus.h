/* This file is part of the GPFS project.
 * Licensing information can be found in the LICENSE file
 * (C) 2014 The GPFS maniacs. All rights reserved.
 */
#ifndef __PLUS_H__
#define __PLUS_H__


/**
 * URL from where the user has to request the token.
 */
static const char REQUEST_URL[] =
  "https://accounts.google.com/o/oauth2/auth\
    ?scope=https://www.googleapis.com/auth/plus.media.upload\
    &redirect_uri=urn:ietf:wg:oauth:2.0:oob\
    &response_type=code\
    &client_id=\
      51706773476-rs349ki03g2pn50l25mcgdfgk3nq8948.apps.googleusercontent.com";


/**
 * Google+ context.
 */
struct plus_ctx
{
  const char *token;
};


void plus_init(struct plus_ctx *);
void plus_auth(struct plus_ctx *);
void plus_free(struct plus_ctx *);


#endif /*__PLUS_H__*/
