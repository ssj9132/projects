import Navbar from '../Components/Navbar.js';
import Shaun from '../Components/Shaun.js';
import About from '../Components/AboutMe.js';
import Skills from '../Components/Skills.js';
import Contacts from '../Components/Contacts.js';
import Footer from '../Components/Footer.js';


export function Home()
{
    return(
        <div id='home'>
            <Navbar />
            <Shaun />
            <About />
            <Skills />
            <Contacts />
            <Footer />
        </div>
    )
}

export default Home;