#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct IResource {
    virtual string snippet() = 0;
    virtual string title() = 0;
    virtual string image() = 0;
    virtual string url() = 0;
};

struct View {
    unique_ptr<IResource> pResource;
    
    public View(IResource* ptr) : pResource(unique_ptr<IResource>(ptr)) {}
    
    virtual string show() = 0;
};

struct LongFormView : View {
    string show() override {
        return string(">>Long Form View<<\n") + 
        pResource->snippet() +
        pResource->title() +
        pResource->image() +
        pResource->url();
    }
};

struct Artist;

struct ArtistResource : IResource {
    unique_ptr<Artist> pArtist;
    ArtistResource(Artist* ptr) : pArtist{unique_ptr<Artist>(ptr)} {}

    string snippet() override {
        return pArtist->getBio();
    }

    string title() override {
        return pArtist->getName();
    }

    string image() override {
        return pArtist->getImage();
    }

    string url() override {
        return pArtist->getURL();
    }
};

class Artist {
    string name;
    string url;
    string image;
    string bio;
    public:
    Artist(string t_name, t_url, t_image, t_bio) : name{move(t_name)},
    url{move(t_url)}, image{move(t_image)}, bio{move(t_bio)} {}
    
    string getBio() const {
        return bio;
    }
    
    string getName() const {
        return name;
    }

    string getImage() const {
        return image;
    }

    string getURL() const {
        return url;
    }
};