#ifndef CLIENTCONFIG_H
#define CLIENTCONFIG_H

#include <aws/core/Aws.h>
class clientConfig : public Aws::Client::ClientConfiguration {
public:
    clientConfig();
};

#endif // CLIENTCONFIG_H
