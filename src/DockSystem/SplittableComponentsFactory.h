#ifndef FFI_RUST_SPLITTABLECOMPONENTSFACTORY_H
#define FFI_RUST_SPLITTABLECOMPONENTSFACTORY_H

#include <DockComponentsFactory.h>
#include <DockAreaTitleBar.h>

class SplittableComponentsFactory : public ads::CDockComponentsFactory
{
public:
    ads::CDockAreaTitleBar* createDockAreaTitleBar(ads::CDockAreaWidget* dock_area) const override;
};


#endif //FFI_RUST_SPLITTABLECOMPONENTSFACTORY_H
