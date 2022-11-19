#include "TestWindow.h"

#include <cassert>
#include <utility>

#include "TestOpenGLContext.h"

TestWindow::TestWindow(std::unique_ptr<PlatformWindow> base, TestStateHandle state) :
    base_(std::move(base)),
    state_(std::move(state)) {
    assert(state_->window == nullptr);
    state_->window = this;
}

TestWindow::~TestWindow() {
    assert(state_->window == this);
    state_->window = nullptr;
}

void TestWindow::SetTitle(const std::string &title) {
    base_->SetTitle(title);
}

std::string TestWindow::Title() const {
    return base_->Title();
}

void TestWindow::Resize(const Sizei &size) {
    base_->Resize(size);
}

Sizei TestWindow::Size() const {
    return base_->Size();
}

void TestWindow::SetPosition(const Pointi &pos) {
    base_->SetPosition(pos);
}

Pointi TestWindow::Position() const {
    return base_->Position();
}

void TestWindow::SetVisible(bool visible) {
    base_->SetVisible(visible);
}

bool TestWindow::IsVisible() const {
    return base_->IsVisible();
}

void TestWindow::SetFullscreen(bool fullscreen) {
    base_->SetFullscreen(fullscreen);
}

bool TestWindow::IsFullscreen() const {
    return base_->IsFullscreen();
}

void TestWindow::SetBorderless(bool borderless) {
    base_->SetBorderless(borderless);
}

bool TestWindow::IsBorderless() const {
    return base_->IsBorderless();
}

void TestWindow::SetGrabsMouse(bool grabsMouse) {
    base_->SetGrabsMouse(grabsMouse);
}

bool TestWindow::GrabsMouse() const {
    return base_->GrabsMouse();
}

void TestWindow::Activate() {
    base_->Activate();
}

uintptr_t TestWindow::SystemHandle() const {
    return base_->SystemHandle();
}

std::unique_ptr<PlatformOpenGLContext> TestWindow::CreateOpenGLContext(const PlatformOpenGLOptions &options) {
    return std::make_unique<TestOpenGLContext>(base_->CreateOpenGLContext(options), state_);
}
