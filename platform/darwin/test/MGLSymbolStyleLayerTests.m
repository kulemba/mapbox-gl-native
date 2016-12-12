// This file is generated. 
// Edit platform/darwin/scripts/generate-style-code.js, then run `make style-code-darwin`.

#import "MGLStyleLayerTests.h"

@interface MGLSymbolLayerTests : MGLStyleLayerTests
@end

@implementation MGLSymbolLayerTests

- (void)testSymbolLayer {
    NSString *filePath = [[NSBundle bundleForClass:self.class] pathForResource:@"amsterdam" ofType:@"geojson"];
    NSURL *url = [NSURL fileURLWithPath:filePath];
    MGLGeoJSONSource *source = [[MGLGeoJSONSource alloc] initWithIdentifier:@"sourceID" URL:url options:nil];
    [self.mapView.style addSource:source];
    MGLSymbolStyleLayer *layer = [[MGLSymbolStyleLayer alloc] initWithIdentifier:@"layerID" source:source];
    [self.mapView.style addLayer:layer];

    layer.iconAllowOverlap = [MGLRuntimeStylingHelper testBool];
    layer.iconIgnorePlacement = [MGLRuntimeStylingHelper testBool];
    layer.iconImageName = [MGLRuntimeStylingHelper testString];
    layer.iconKeepUpright = [MGLRuntimeStylingHelper testBool];
    layer.iconOffset = [MGLRuntimeStylingHelper testOffset];
    layer.iconOptional = [MGLRuntimeStylingHelper testBool];
    layer.iconPadding = [MGLRuntimeStylingHelper testNumber];
    layer.iconRotate = [MGLRuntimeStylingHelper testNumber];
    layer.iconRotationAlignment = [MGLRuntimeStylingHelper testEnum:MGLIconRotationAlignmentAuto type:@encode(MGLIconRotationAlignment)];
    layer.iconSize = [MGLRuntimeStylingHelper testNumber];
    layer.iconTextFit = [MGLRuntimeStylingHelper testEnum:MGLIconTextFitBoth type:@encode(MGLIconTextFit)];
    layer.iconTextFitPadding = [MGLRuntimeStylingHelper testPadding];
    layer.symbolAvoidEdges = [MGLRuntimeStylingHelper testBool];
    layer.symbolPlacement = [MGLRuntimeStylingHelper testEnum:MGLSymbolPlacementLine type:@encode(MGLSymbolPlacement)];
    layer.symbolSpacing = [MGLRuntimeStylingHelper testNumber];
    layer.textAllowOverlap = [MGLRuntimeStylingHelper testBool];
    layer.textAnchor = [MGLRuntimeStylingHelper testEnum:MGLTextAnchorBottomRight type:@encode(MGLTextAnchor)];
    layer.textField = [MGLRuntimeStylingHelper testString];
    layer.textFont = [MGLRuntimeStylingHelper testFont];
    layer.textIgnorePlacement = [MGLRuntimeStylingHelper testBool];
    layer.textJustify = [MGLRuntimeStylingHelper testEnum:MGLTextJustifyRight type:@encode(MGLTextJustify)];
    layer.textKeepUpright = [MGLRuntimeStylingHelper testBool];
    layer.textLetterSpacing = [MGLRuntimeStylingHelper testNumber];
    layer.textLineHeight = [MGLRuntimeStylingHelper testNumber];
    layer.textMaxAngle = [MGLRuntimeStylingHelper testNumber];
    layer.textMaxWidth = [MGLRuntimeStylingHelper testNumber];
    layer.textOffset = [MGLRuntimeStylingHelper testOffset];
    layer.textOptional = [MGLRuntimeStylingHelper testBool];
    layer.textPadding = [MGLRuntimeStylingHelper testNumber];
    layer.textPitchAlignment = [MGLRuntimeStylingHelper testEnum:MGLTextPitchAlignmentAuto type:@encode(MGLTextPitchAlignment)];
    layer.textRotate = [MGLRuntimeStylingHelper testNumber];
    layer.textRotationAlignment = [MGLRuntimeStylingHelper testEnum:MGLTextRotationAlignmentAuto type:@encode(MGLTextRotationAlignment)];
    layer.textSize = [MGLRuntimeStylingHelper testNumber];
    layer.textTransform = [MGLRuntimeStylingHelper testEnum:MGLTextTransformLowercase type:@encode(MGLTextTransform)];
    layer.iconColor = [MGLRuntimeStylingHelper testColor];
    layer.iconHaloBlur = [MGLRuntimeStylingHelper testNumber];
    layer.iconHaloColor = [MGLRuntimeStylingHelper testColor];
    layer.iconHaloWidth = [MGLRuntimeStylingHelper testNumber];
    layer.iconOpacity = [MGLRuntimeStylingHelper testNumber];
    layer.iconTranslate = [MGLRuntimeStylingHelper testOffset];
    layer.iconTranslateAnchor = [MGLRuntimeStylingHelper testEnum:MGLIconTranslateAnchorViewport type:@encode(MGLIconTranslateAnchor)];
    layer.textColor = [MGLRuntimeStylingHelper testColor];
    layer.textHaloBlur = [MGLRuntimeStylingHelper testNumber];
    layer.textHaloColor = [MGLRuntimeStylingHelper testColor];
    layer.textHaloWidth = [MGLRuntimeStylingHelper testNumber];
    layer.textOpacity = [MGLRuntimeStylingHelper testNumber];
    layer.textTranslate = [MGLRuntimeStylingHelper testOffset];
    layer.textTranslateAnchor = [MGLRuntimeStylingHelper testEnum:MGLTextTranslateAnchorViewport type:@encode(MGLTextTranslateAnchor)];

    MGLSymbolStyleLayer *gLayer = (MGLSymbolStyleLayer *)[self.mapView.style layerWithIdentifier:@"layerID"];
    XCTAssertTrue([gLayer isKindOfClass:[MGLSymbolStyleLayer class]]);
    XCTAssertEqualObjects(gLayer.iconAllowOverlap, [MGLRuntimeStylingHelper testBool]);
    XCTAssertEqualObjects(gLayer.iconIgnorePlacement, [MGLRuntimeStylingHelper testBool]);
    XCTAssertEqualObjects(gLayer.iconImageName, [MGLRuntimeStylingHelper testString]);
    XCTAssertEqualObjects(gLayer.iconKeepUpright, [MGLRuntimeStylingHelper testBool]);
    XCTAssertEqualObjects(gLayer.iconOffset, [MGLRuntimeStylingHelper testOffset]);
    XCTAssertEqualObjects(gLayer.iconOptional, [MGLRuntimeStylingHelper testBool]);
    XCTAssertEqualObjects(gLayer.iconPadding, [MGLRuntimeStylingHelper testNumber]);
    XCTAssertEqualObjects(gLayer.iconRotate, [MGLRuntimeStylingHelper testNumber]);
    XCTAssert([gLayer.iconRotationAlignment isKindOfClass:[MGLStyleConstantValue class]]);
    XCTAssertEqualObjects(gLayer.iconRotationAlignment, [MGLRuntimeStylingHelper testEnum:MGLIconRotationAlignmentAuto type:@encode(MGLIconRotationAlignment)]);
    XCTAssertEqualObjects(gLayer.iconSize, [MGLRuntimeStylingHelper testNumber]);
    XCTAssert([gLayer.iconTextFit isKindOfClass:[MGLStyleConstantValue class]]);
    XCTAssertEqualObjects(gLayer.iconTextFit, [MGLRuntimeStylingHelper testEnum:MGLIconTextFitBoth type:@encode(MGLIconTextFit)]);
    XCTAssertEqualObjects(gLayer.iconTextFitPadding, [MGLRuntimeStylingHelper testPadding]);
    XCTAssertEqualObjects(gLayer.symbolAvoidEdges, [MGLRuntimeStylingHelper testBool]);
    XCTAssert([gLayer.symbolPlacement isKindOfClass:[MGLStyleConstantValue class]]);
    XCTAssertEqualObjects(gLayer.symbolPlacement, [MGLRuntimeStylingHelper testEnum:MGLSymbolPlacementLine type:@encode(MGLSymbolPlacement)]);
    XCTAssertEqualObjects(gLayer.symbolSpacing, [MGLRuntimeStylingHelper testNumber]);
    XCTAssertEqualObjects(gLayer.textAllowOverlap, [MGLRuntimeStylingHelper testBool]);
    XCTAssert([gLayer.textAnchor isKindOfClass:[MGLStyleConstantValue class]]);
    XCTAssertEqualObjects(gLayer.textAnchor, [MGLRuntimeStylingHelper testEnum:MGLTextAnchorBottomRight type:@encode(MGLTextAnchor)]);
    XCTAssertEqualObjects(gLayer.textField, [MGLRuntimeStylingHelper testString]);
    XCTAssertEqualObjects(gLayer.textFont, [MGLRuntimeStylingHelper testFont]);
    XCTAssertEqualObjects(gLayer.textIgnorePlacement, [MGLRuntimeStylingHelper testBool]);
    XCTAssert([gLayer.textJustify isKindOfClass:[MGLStyleConstantValue class]]);
    XCTAssertEqualObjects(gLayer.textJustify, [MGLRuntimeStylingHelper testEnum:MGLTextJustifyRight type:@encode(MGLTextJustify)]);
    XCTAssertEqualObjects(gLayer.textKeepUpright, [MGLRuntimeStylingHelper testBool]);
    XCTAssertEqualObjects(gLayer.textLetterSpacing, [MGLRuntimeStylingHelper testNumber]);
    XCTAssertEqualObjects(gLayer.textLineHeight, [MGLRuntimeStylingHelper testNumber]);
    XCTAssertEqualObjects(gLayer.textMaxAngle, [MGLRuntimeStylingHelper testNumber]);
    XCTAssertEqualObjects(gLayer.textMaxWidth, [MGLRuntimeStylingHelper testNumber]);
    XCTAssertEqualObjects(gLayer.textOffset, [MGLRuntimeStylingHelper testOffset]);
    XCTAssertEqualObjects(gLayer.textOptional, [MGLRuntimeStylingHelper testBool]);
    XCTAssertEqualObjects(gLayer.textPadding, [MGLRuntimeStylingHelper testNumber]);
    XCTAssert([gLayer.textPitchAlignment isKindOfClass:[MGLStyleConstantValue class]]);
    XCTAssertEqualObjects(gLayer.textPitchAlignment, [MGLRuntimeStylingHelper testEnum:MGLTextPitchAlignmentAuto type:@encode(MGLTextPitchAlignment)]);
    XCTAssertEqualObjects(gLayer.textRotate, [MGLRuntimeStylingHelper testNumber]);
    XCTAssert([gLayer.textRotationAlignment isKindOfClass:[MGLStyleConstantValue class]]);
    XCTAssertEqualObjects(gLayer.textRotationAlignment, [MGLRuntimeStylingHelper testEnum:MGLTextRotationAlignmentAuto type:@encode(MGLTextRotationAlignment)]);
    XCTAssertEqualObjects(gLayer.textSize, [MGLRuntimeStylingHelper testNumber]);
    XCTAssert([gLayer.textTransform isKindOfClass:[MGLStyleConstantValue class]]);
    XCTAssertEqualObjects(gLayer.textTransform, [MGLRuntimeStylingHelper testEnum:MGLTextTransformLowercase type:@encode(MGLTextTransform)]);
    XCTAssertEqualObjects(gLayer.iconColor, [MGLRuntimeStylingHelper testColor]);
    XCTAssertEqualObjects(gLayer.iconHaloBlur, [MGLRuntimeStylingHelper testNumber]);
    XCTAssertEqualObjects(gLayer.iconHaloColor, [MGLRuntimeStylingHelper testColor]);
    XCTAssertEqualObjects(gLayer.iconHaloWidth, [MGLRuntimeStylingHelper testNumber]);
    XCTAssertEqualObjects(gLayer.iconOpacity, [MGLRuntimeStylingHelper testNumber]);
    XCTAssertEqualObjects(gLayer.iconTranslate, [MGLRuntimeStylingHelper testOffset]);
    XCTAssert([gLayer.iconTranslateAnchor isKindOfClass:[MGLStyleConstantValue class]]);
    XCTAssertEqualObjects(gLayer.iconTranslateAnchor, [MGLRuntimeStylingHelper testEnum:MGLIconTranslateAnchorViewport type:@encode(MGLIconTranslateAnchor)]);
    XCTAssertEqualObjects(gLayer.textColor, [MGLRuntimeStylingHelper testColor]);
    XCTAssertEqualObjects(gLayer.textHaloBlur, [MGLRuntimeStylingHelper testNumber]);
    XCTAssertEqualObjects(gLayer.textHaloColor, [MGLRuntimeStylingHelper testColor]);
    XCTAssertEqualObjects(gLayer.textHaloWidth, [MGLRuntimeStylingHelper testNumber]);
    XCTAssertEqualObjects(gLayer.textOpacity, [MGLRuntimeStylingHelper testNumber]);
    XCTAssertEqualObjects(gLayer.textTranslate, [MGLRuntimeStylingHelper testOffset]);
    XCTAssert([gLayer.textTranslateAnchor isKindOfClass:[MGLStyleConstantValue class]]);
    XCTAssertEqualObjects(gLayer.textTranslateAnchor, [MGLRuntimeStylingHelper testEnum:MGLTextTranslateAnchorViewport type:@encode(MGLTextTranslateAnchor)]);

    layer.iconAllowOverlap = [MGLRuntimeStylingHelper testBoolFunction];
    layer.iconIgnorePlacement = [MGLRuntimeStylingHelper testBoolFunction];
    layer.iconImageName = [MGLRuntimeStylingHelper testStringFunction];
    layer.iconKeepUpright = [MGLRuntimeStylingHelper testBoolFunction];
    layer.iconOffset = [MGLRuntimeStylingHelper testOffsetFunction];
    layer.iconOptional = [MGLRuntimeStylingHelper testBoolFunction];
    layer.iconPadding = [MGLRuntimeStylingHelper testNumberFunction];
    layer.iconRotate = [MGLRuntimeStylingHelper testNumberFunction];
    layer.iconRotationAlignment = [MGLRuntimeStylingHelper testEnumFunction:MGLIconRotationAlignmentAuto type:@encode(MGLIconRotationAlignment)];
    layer.iconSize = [MGLRuntimeStylingHelper testNumberFunction];
    layer.iconTextFit = [MGLRuntimeStylingHelper testEnumFunction:MGLIconTextFitBoth type:@encode(MGLIconTextFit)];
    layer.iconTextFitPadding = [MGLRuntimeStylingHelper testPaddingFunction];
    layer.symbolAvoidEdges = [MGLRuntimeStylingHelper testBoolFunction];
    layer.symbolPlacement = [MGLRuntimeStylingHelper testEnumFunction:MGLSymbolPlacementLine type:@encode(MGLSymbolPlacement)];
    layer.symbolSpacing = [MGLRuntimeStylingHelper testNumberFunction];
    layer.textAllowOverlap = [MGLRuntimeStylingHelper testBoolFunction];
    layer.textAnchor = [MGLRuntimeStylingHelper testEnumFunction:MGLTextAnchorBottomRight type:@encode(MGLTextAnchor)];
    layer.textField = [MGLRuntimeStylingHelper testStringFunction];
    layer.textFont = [MGLRuntimeStylingHelper testFontFunction];
    layer.textIgnorePlacement = [MGLRuntimeStylingHelper testBoolFunction];
    layer.textJustify = [MGLRuntimeStylingHelper testEnumFunction:MGLTextJustifyRight type:@encode(MGLTextJustify)];
    layer.textKeepUpright = [MGLRuntimeStylingHelper testBoolFunction];
    layer.textLetterSpacing = [MGLRuntimeStylingHelper testNumberFunction];
    layer.textLineHeight = [MGLRuntimeStylingHelper testNumberFunction];
    layer.textMaxAngle = [MGLRuntimeStylingHelper testNumberFunction];
    layer.textMaxWidth = [MGLRuntimeStylingHelper testNumberFunction];
    layer.textOffset = [MGLRuntimeStylingHelper testOffsetFunction];
    layer.textOptional = [MGLRuntimeStylingHelper testBoolFunction];
    layer.textPadding = [MGLRuntimeStylingHelper testNumberFunction];
    layer.textPitchAlignment = [MGLRuntimeStylingHelper testEnumFunction:MGLTextPitchAlignmentAuto type:@encode(MGLTextPitchAlignment)];
    layer.textRotate = [MGLRuntimeStylingHelper testNumberFunction];
    layer.textRotationAlignment = [MGLRuntimeStylingHelper testEnumFunction:MGLTextRotationAlignmentAuto type:@encode(MGLTextRotationAlignment)];
    layer.textSize = [MGLRuntimeStylingHelper testNumberFunction];
    layer.textTransform = [MGLRuntimeStylingHelper testEnumFunction:MGLTextTransformLowercase type:@encode(MGLTextTransform)];
    layer.iconColor = [MGLRuntimeStylingHelper testColorFunction];
    layer.iconHaloBlur = [MGLRuntimeStylingHelper testNumberFunction];
    layer.iconHaloColor = [MGLRuntimeStylingHelper testColorFunction];
    layer.iconHaloWidth = [MGLRuntimeStylingHelper testNumberFunction];
    layer.iconOpacity = [MGLRuntimeStylingHelper testNumberFunction];
    layer.iconTranslate = [MGLRuntimeStylingHelper testOffsetFunction];
    layer.iconTranslateAnchor = [MGLRuntimeStylingHelper testEnumFunction:MGLIconTranslateAnchorViewport type:@encode(MGLIconTranslateAnchor)];
    layer.textColor = [MGLRuntimeStylingHelper testColorFunction];
    layer.textHaloBlur = [MGLRuntimeStylingHelper testNumberFunction];
    layer.textHaloColor = [MGLRuntimeStylingHelper testColorFunction];
    layer.textHaloWidth = [MGLRuntimeStylingHelper testNumberFunction];
    layer.textOpacity = [MGLRuntimeStylingHelper testNumberFunction];
    layer.textTranslate = [MGLRuntimeStylingHelper testOffsetFunction];
    layer.textTranslateAnchor = [MGLRuntimeStylingHelper testEnumFunction:MGLTextTranslateAnchorViewport type:@encode(MGLTextTranslateAnchor)];

    XCTAssertEqualObjects(gLayer.iconAllowOverlap, [MGLRuntimeStylingHelper testBoolFunction]);
    XCTAssertEqualObjects(gLayer.iconIgnorePlacement, [MGLRuntimeStylingHelper testBoolFunction]);
    XCTAssertEqualObjects(gLayer.iconImageName, [MGLRuntimeStylingHelper testStringFunction]);
    XCTAssertEqualObjects(gLayer.iconKeepUpright, [MGLRuntimeStylingHelper testBoolFunction]);
    XCTAssertEqualObjects(gLayer.iconOffset, [MGLRuntimeStylingHelper testOffsetFunction]);
    XCTAssertEqualObjects(gLayer.iconOptional, [MGLRuntimeStylingHelper testBoolFunction]);
    XCTAssertEqualObjects(gLayer.iconPadding, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.iconRotate, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.iconRotationAlignment, [MGLRuntimeStylingHelper testEnumFunction:MGLIconRotationAlignmentAuto type:@encode(MGLIconRotationAlignment)]);
    XCTAssertEqualObjects(gLayer.iconSize, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.iconTextFit, [MGLRuntimeStylingHelper testEnumFunction:MGLIconTextFitBoth type:@encode(MGLIconTextFit)]);
    XCTAssertEqualObjects(gLayer.iconTextFitPadding, [MGLRuntimeStylingHelper testPaddingFunction]);
    XCTAssertEqualObjects(gLayer.symbolAvoidEdges, [MGLRuntimeStylingHelper testBoolFunction]);
    XCTAssertEqualObjects(gLayer.symbolPlacement, [MGLRuntimeStylingHelper testEnumFunction:MGLSymbolPlacementLine type:@encode(MGLSymbolPlacement)]);
    XCTAssertEqualObjects(gLayer.symbolSpacing, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.textAllowOverlap, [MGLRuntimeStylingHelper testBoolFunction]);
    XCTAssertEqualObjects(gLayer.textAnchor, [MGLRuntimeStylingHelper testEnumFunction:MGLTextAnchorBottomRight type:@encode(MGLTextAnchor)]);
    XCTAssertEqualObjects(gLayer.textField, [MGLRuntimeStylingHelper testStringFunction]);
    XCTAssertEqualObjects(gLayer.textFont, [MGLRuntimeStylingHelper testFontFunction]);
    XCTAssertEqualObjects(gLayer.textIgnorePlacement, [MGLRuntimeStylingHelper testBoolFunction]);
    XCTAssertEqualObjects(gLayer.textJustify, [MGLRuntimeStylingHelper testEnumFunction:MGLTextJustifyRight type:@encode(MGLTextJustify)]);
    XCTAssertEqualObjects(gLayer.textKeepUpright, [MGLRuntimeStylingHelper testBoolFunction]);
    XCTAssertEqualObjects(gLayer.textLetterSpacing, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.textLineHeight, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.textMaxAngle, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.textMaxWidth, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.textOffset, [MGLRuntimeStylingHelper testOffsetFunction]);
    XCTAssertEqualObjects(gLayer.textOptional, [MGLRuntimeStylingHelper testBoolFunction]);
    XCTAssertEqualObjects(gLayer.textPadding, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.textPitchAlignment, [MGLRuntimeStylingHelper testEnumFunction:MGLTextPitchAlignmentAuto type:@encode(MGLTextPitchAlignment)]);
    XCTAssertEqualObjects(gLayer.textRotate, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.textRotationAlignment, [MGLRuntimeStylingHelper testEnumFunction:MGLTextRotationAlignmentAuto type:@encode(MGLTextRotationAlignment)]);
    XCTAssertEqualObjects(gLayer.textSize, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.textTransform, [MGLRuntimeStylingHelper testEnumFunction:MGLTextTransformLowercase type:@encode(MGLTextTransform)]);
    XCTAssertEqualObjects(gLayer.iconColor, [MGLRuntimeStylingHelper testColorFunction]);
    XCTAssertEqualObjects(gLayer.iconHaloBlur, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.iconHaloColor, [MGLRuntimeStylingHelper testColorFunction]);
    XCTAssertEqualObjects(gLayer.iconHaloWidth, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.iconOpacity, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.iconTranslate, [MGLRuntimeStylingHelper testOffsetFunction]);
    XCTAssertEqualObjects(gLayer.iconTranslateAnchor, [MGLRuntimeStylingHelper testEnumFunction:MGLIconTranslateAnchorViewport type:@encode(MGLIconTranslateAnchor)]);
    XCTAssertEqualObjects(gLayer.textColor, [MGLRuntimeStylingHelper testColorFunction]);
    XCTAssertEqualObjects(gLayer.textHaloBlur, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.textHaloColor, [MGLRuntimeStylingHelper testColorFunction]);
    XCTAssertEqualObjects(gLayer.textHaloWidth, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.textOpacity, [MGLRuntimeStylingHelper testNumberFunction]);
    XCTAssertEqualObjects(gLayer.textTranslate, [MGLRuntimeStylingHelper testOffsetFunction]);
    XCTAssertEqualObjects(gLayer.textTranslateAnchor, [MGLRuntimeStylingHelper testEnumFunction:MGLTextTranslateAnchorViewport type:@encode(MGLTextTranslateAnchor)]);
}

@end
