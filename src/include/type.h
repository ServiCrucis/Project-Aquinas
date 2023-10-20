//
// Created by Andrew on 10/9/2023.
//

#ifndef PROJECT_AQUINAS_TYPE_H
#define PROJECT_AQUINAS_TYPE_H

#define typecast(type, member, object) ( (type) *((&object) + offsetof(typeof(object), object.member)) )

#endif //PROJECT_AQUINAS_TYPE_H
