ssh slave1 << END
if ! [[ -d mpi_demo ]]; then 
	git clone https://github.com/kailaix/mpi_demo.git
else 
	cd mpi_demo
	git pull
fi
END

ssh slave2 << END
if ! [[ -d mpi_demo ]]; then
        git clone https://github.com/kailaix/mpi_demo.git
else
        cd mpi_demo
        git pull
fi
END
