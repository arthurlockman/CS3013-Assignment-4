
Vagrant.configure("2") do |config|
    config.vm.box = "ubuntu/vivid64"
    config.vm.provision :shell, path: "bootstrap.sh"
    config.vm.hostname = "cs3013proj4"
    config.vm.provider "virtualbox" do |v|
        v.name = "cs3013-project4"
        v.memory = 2048
        v.cpus = 2
    end
end
