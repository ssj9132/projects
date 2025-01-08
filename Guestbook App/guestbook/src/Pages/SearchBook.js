import OldVisNav from '../Components/OldVisNav';
import Search from '../Components/Searchbar';



export function OldVis() {
    return (
      <div className="Home">
        <nav>
          <OldVisNav />
        </nav>
        <body><Search /></body>
      
      </div>
    );
  }
  
  export default OldVis;