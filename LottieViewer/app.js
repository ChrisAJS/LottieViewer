var App = ((function(){
    var App = function(targetElement) {
        this.element = targetElement;
        this.animation = null;
    };

    App.prototype.loadAnimation = function(animData) {
        bodymovin.destroy();
        this.animation = bodymovin.loadAnimation({
          container: this.element,
          animationData: JSON.parse(animData),
          renderer: 'svg',
          loop: true,
          autoplay: true
        });
    };

    App.prototype.frameCount = function() {
        return this.animation.getDuration(true);
    };

    App.prototype.frameRate = function() {
        return this.frameCount() / this.animation.getDuration(false);
    };

    App.prototype.play = function() {
        this.animation.play();
    };

    App.prototype.pause = function() {
        this.animation.pause();
    };

    App.prototype.seek = function(frame) {
        this.animation.goToAndStop(frame, true);
    };

    App.prototype.onEnterFrame = function(cb) {
        this.animation.onEnterFrame = function(e) { cb(e.currentTime) };
    };

    App.prototype.setSpeed = function(speed) {
        this.animation.setSpeed(speed);
    };

    return App;
}))();

document.addEventListener("DOMContentLoaded", function(event) {
    var app = new App(document.getElementById("lottie"));
    var webChannel = new QWebChannel(qt.webChannelTransport, function(channel){
        window.external = channel.objects.external;
        window.external.displayAnimation.connect(function(animData){
            app.loadAnimation(animData);
            window.external.animationLoaded(app.frameCount(), app.frameRate());
            app.onEnterFrame(function(frame) {
              window.external.enteredFrame(frame);
            });
        });

        window.external.playAnimation.connect(function() {
           app.play();
        });

        window.external.pauseAnimation.connect(function() {
           app.pause();
        });

        window.external.seekToFrame.connect(function(frame) {
           app.seek(frame);
        });

        window.external.setSpeed.connect(function(speed) {
           app.setSpeed(speed/100.0);
        });
    });
});
