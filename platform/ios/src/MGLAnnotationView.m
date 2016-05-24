#import "MGLAnnotationView.h"
#import "MGLAnnotationView_Private.h"

@interface MGLAnnotationView ()

@property (nonatomic) id<MGLAnnotation> annotation;
@property (nonatomic, readwrite, nullable) NSString *reuseIdentifier;

@end

@implementation MGLAnnotationView

- (instancetype)initWithReuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super init];
    
    if (self)
    {
        _reuseIdentifier = [reuseIdentifier copy];
    }
    
    return self;
}

- (void)prepareForReuse
{
    // Intentionally left blank. The default implementation of this method does nothing.
}

- (id<CAAction>)actionForLayer:(CALayer *)layer forKey:(NSString *)event
{
    // Allow mbgl to drive animation of this view’s bounds.
    if ([event isEqualToString:@"bounds"])
    {
        return [NSNull null];
    }
    return [super actionForLayer:layer forKey:event];
}

@end