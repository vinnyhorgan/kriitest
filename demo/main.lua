function krii.conf(t)
    t.title = "Krii Demo"
end

function krii.init()
    krii.log("Helloooo")
end

function krii.update(dt)

end

function krii.draw()
    krii.graphics.rectangle("fill", 0, 0, 100, 100)

    krii.graphics.circle("line", 100, 100, 50)

    krii.graphics.print("Hello Krii!", 300, 300)
end

function krii.draw3d()
    krii.graphics.grid()
end

function krii.gui()

end